#include "bubblesoverlay.hh"
#include "downloadsicon.hh"
#include <QPainter>
#include <QPen>
#include <QApplication>
#include <QStyle>
#include <iostream>
#include <algorithm>
using namespace std;

// This is dirty, but it's good enough for now.
extern QApplication *app;


BubblesOverlay::BubblesOverlay(QWidget *parent)
	: QWidget(parent), m_deleteButton(0,0,150,150)
{
	setPalette(Qt::transparent);
	setAttribute(Qt::WA_TransparentForMouseEvents);
	// See resizeEvent() for the positioning of m_deleteButton.
}


void BubblesOverlay::mouseMEvent(QMouseEvent * event) {
	m_mousex = event->x(); m_mousey = event->y();
	bool accepted = false;
	for(QVector<Bubble*>::size_type i = 0; i < m_bubbles.size(); ++i)
		if(m_bubbles[i]->clicked()) {
			accepted = true;
			updateBubbles();
			break;
		}
	if (!accepted) event->ignore();
	else event->accept();
}


void BubblesOverlay::mousePEvent(QMouseEvent * event) {
	m_mousex = event->x(); m_mousey = event->y();
	if (event->button() == Qt::LeftButton) {
		bool clicked = false;
		for(QVector<Bubble*>::size_type i = 0; i < m_bubbles.size(); ++i) {
			if(m_bubbles[i]->bounds().contains(m_mousex, m_mousey)){
				clicked = true;
				m_bubbles[i]->setClicked(true);
				//m_bubbles[i]->output();
				break;
			}
		}
		if (clicked) event->accept();
		else event->ignore();
		updateBubbles();
	}
}


void BubblesOverlay::mouseREvent(QMouseEvent *event) {
	m_mousex = event->x(); m_mousey = event->y();
	if (event->button() == Qt::LeftButton){
		for(QVector<Bubble*>::size_type i = m_bubbles.size()-1; i >= 0; --i){
			m_bubbles[i]->setClicked(false);
			//m_bubbles[i]->output();

			// If this bubble is sitting overtop of the delete button, then
			// delete it.
			if (m_deleteButton.contains(m_bubbles[i]->bounds())) {
				disconnect(m_bubbles[i], SIGNAL(changed()), this, SLOT(updateProgress()));
				delete m_bubbles[i];
				m_bubbles.removeAt(i);
			}
		}
		updateBubbles();
	}
	event->ignore();
}


// Comparision function for sorting - see below.
static bool sortComp(Bubble *a, Bubble *b) {
	return a->bounds().y() < b->bounds().y();
}

void BubblesOverlay::updateBubbles() {
	//cout<<"made to update"<<endl;

	/* The approach here is not too difficult, and avoids any wierd collision math.
	 * First, if a bubble is being dragged, then just keep dragging it, otherwise
	 * find the side it is closest to and add it to the appropriate "snap" list.
	 * Sort these snap lists in order of y. Then just pack the bubbles
	 * together on each side. We will assume that we don't overflow the space
	 * available. */

	QVector<Bubble*> left, right;
	qreal leftSize = 0, rightSize = 0; // in pixels

	for(int i = 0; i < m_bubbles.size(); ++i){
		Bubble *bb = m_bubbles[i];
		// drag
		if(bb->clicked()){
			//cout<<"dragging"<<endl; //TC
			bb->setPos(QPointF(m_mousex - bb->bounds().width()/2,
							   m_mousey - bb->bounds().height()/2));
		}
		// snap to either left or right
		else if (bb->bounds().x() < width()/2 - bb->bounds().width()/2) {
			left.push_back(bb);
			leftSize += bb->bounds().height() + 5; // for padding
		}
		else {
			right.push_back(bb);
			rightSize += bb->bounds().height() + 5;
		}
	}

	sort(left.begin(), left.end(), sortComp);
	sort(right.begin(), right.end(), sortComp);

	qreal y = height()/2 - leftSize/2;
	for (int i = 0; i < left.size(); ++i) {
		qreal size = left[i]->bounds().width();
		left[i]->setDest(QPointF(5, y));
		y += size + 5;
	}
	y = height()/2 - rightSize/2;
	for (int i = 0; i < right.size(); ++i) {
		qreal size = right[i]->bounds().width();
		// So that we aren't overlapping the scrollbars ...
		qreal scrollWidth = app->style()->pixelMetric(QStyle::PM_ScrollBarExtent);
		right[i]->setDest(QPointF(width()-size - scrollWidth-5, y));
		y += size + 5;
	}

	update();
}


void BubblesOverlay::downloadRequested(const QUrl &url) {
	m_bubbles.push_front(new Bubble(url, this));
	connect(m_bubbles.front(), SIGNAL(changed()), this, SLOT(update()));

	updateBubbles();
}


void BubblesOverlay::resizeEvent(QResizeEvent *event) {
	qreal scrollWidth = app->style()->pixelMetric(QStyle::PM_ScrollBarExtent);

	// Put the delete button at the bottom-middle. Adjust as needed.
	m_deleteButton.moveTo(width()/2-m_deleteButton.width()/2,
						  height()-m_deleteButton.height()-scrollWidth);

	updateBubbles();
	event->accept();
}


void BubblesOverlay::paintEvent(QPaintEvent *){
	//setup
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);
	painter.setPen(Qt::green);

	//if a bubble is clicked
	int dragging = -1;
	for(QVector<Bubble*>::size_type i = 0; i < m_bubbles.size(); ++i)
		if(m_bubbles[i]->clicked())
			dragging = i;

	//draw the delete button
	if(dragging >= 0){
		QPen wthick;
		wthick.setColor(Qt::red);
		if (m_deleteButton.contains(m_bubbles[dragging]->bounds()))
			wthick.setWidth(4);
		else
			wthick.setWidth(1);
		painter.setPen(wthick);
		painter.drawRoundedRect(m_deleteButton, 15, 15);

		wthick.setWidth(4);
		painter.setPen(wthick);
		painter.setBrush(QBrush(Qt::red));
		painter.drawEllipse(m_deleteButton.center(), 25, 25);

		wthick.setColor(Qt::white);
		painter.setPen(wthick);

		/* TODO
		painter.drawLine(QPoint((-(BSIZE/2.0)) + (BSIZE/4.0),(WSIZE/2.0) - BSIZE + (BSIZE/4.0)),
						 QPoint((BSIZE/2.0) - (BSIZE/4),(WSIZE/2) - (BSIZE/4.0)));
		painter.drawLine(QPoint(((BSIZE/2.0)) - (BSIZE/4.0),(WSIZE/2.0) - BSIZE + (BSIZE/4.0)),
						 QPoint(-(BSIZE/2.0) + (BSIZE/4.0),(WSIZE/2.0) - (BSIZE/4.0)));
		*/
	}

	for(QVector<Bubble*>::size_type i = 0; i < m_bubbles.size(); i++)
		m_bubbles[i]->paint(&painter);
}

