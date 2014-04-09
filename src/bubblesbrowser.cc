#include "bubblesbrowser.hh"
#include "bubblesoverlay.hh"
#include "bubbleswebview.hh"

#include <QNetworkReply>
#include <iostream>
#include <QResizeEvent>
#include <cmath>
using namespace std;


BubblesBrowser::BubblesBrowser(QString startPage, QWidget *parent)
	: BasicBrowser(startPage, parent)
{
	m_bubblesOverlay = new BubblesOverlay(m_webView);
	connect(m_webView, SIGNAL(mouseMEvent(QMouseEvent*)), m_bubblesOverlay, SLOT(mouseMEvent(QMouseEvent*)));
	connect(m_webView, SIGNAL(mousePEvent(QMouseEvent*)), m_bubblesOverlay, SLOT(mousePEvent(QMouseEvent*)));
	connect(m_webView, SIGNAL(mouseREvent(QMouseEvent*)), m_bubblesOverlay, SLOT(mouseREvent(QMouseEvent*)));
}


/*
bool BubblesBrowser::overlapping(Bubble* b1, Bubble* b2, int tol){
	cout<<"check overlap"<<endl;
	double TOLERANCE = tol;
	int disX, disY;
	// If b2 is null, then we only care about if it's over the delete button.
	if(!b2) {
		cout<<"ifnull"<<endl;
		disX = abs(b1->getX());
		disY = abs(WSIZE/2 - b1->getY() - BSIZE/2);
	}
	else {
		disX = abs(b1->getX() - b2->getX());
		disY = abs(b1->getY() - b2->getY());
	}
	cout<<"disx"<<disX<<"disY"<<disY<<endl;
	TOLERANCE = (TOLERANCE/100);
	if(disY <= TOLERANCE && disX <= TOLERANCE){
		cout<<"returning Overlapping"<<endl; //TC
		return 1;
	}
	else
		cout<<"disy"<<disY<<"disx"<<disX<<endl;//TC
	return 0;
}

void BubblesBrowser::updateBubbles(){
	cout<<"made to update"<<endl;
	for(QVector<Bubble*>::size_type i = 0; i < m_bubbles.size(); ++i){
		Bubble *bb = m_bubbles[i];
		// keep within bounds
		if (bb->bounds().x() < 0 || bb->bounds().x >= m_bubblesOverlay->width() ||
			bb->bounds().y() < 0 || bb->bounds().y() >= m_bubblesOverlay->height())
		{
			cout<<"out of bounds"<<bb->bounds().x()<<" "<<bb->bounds().y()<<endl;
			bb->setClicked(0);
			qreal nx = max(0, min(bb->bounds().x(), m_bubblesOverlay->width()-1));
			qreal ny = max(0, min(bb->bounds().y(), m_bubblesOverlay->height()-1));
			bb->setPos(QPointF(nx,ny));
		}

		// drag
		if(bb->clicked()){
			cout<<"dragging"<<endl; //TC
			bb->setPos(QPointF(m_mousex, m_mousey));
		}

		//delete
		if(!bb->clicked() && m_deleteButton.){
			cout<<"delete"<<endl;
			delete m_bubbles[i];
			m_bubbles.remove(i);
			m_bubblesOverlay->update();
		}

		//keep on edge
		else if(!m_bubbles[i]->clicked()){
			cout<<"koe"<<endl;//TC
			if(m_bubbles[i]->getX() > -(WSIZE/2.0) + BSIZE/1.75){
				cout<<"not at edge"<<endl;
				m_bubbles[i]->getXref() = m_bubbles[i]->getX()-(WSIZE/500);
				m_bubblesOverlay->update();
				updateBubbles();
			}
			else if(m_bubbles[i]->getX() < -(WSIZE/2.0) + BSIZE/2.3){
				cout<<"too close to edge"<<endl;
				m_bubbles[i]->getXref() = -(WSIZE/2.0) + BSIZE/1.75;
				m_bubblesOverlay->update();
				updateBubbles();
			}
		}

		//prevent overlap
		cout<<"started overlap check"<<endl; //TC
		for(QVector<Bubble*>::size_type j = 0; j < m_bubbles.size(); ++j){
			if(j != i && overlapping(m_bubbles[i], m_bubbles[j], 110)){
				if(m_bubbles[i]->getY() <= m_bubbles[j]->getY()){
					cout<<"iuY"<<m_bubbles[i]->getY()<<"jY"<<m_bubbles[j]->getY()<<endl;
					m_bubbles[i]->getYref() = m_bubbles[i]->getY() - BSIZE/8;
					m_bubbles[j]->getYref() = m_bubbles[j]->getY() + BSIZE/8;
				}
				else{
					cout<<"idY"<<m_bubbles[i]->getY()<<"jY"<<m_bubbles[j]->getY()<<endl;
					m_bubbles[i]->getYref() = m_bubbles[i]->getY() + BSIZE/8;
					m_bubbles[j]->getYref() = m_bubbles[j]->getY() - BSIZE/8;
				}
				m_bubblesOverlay->update();
				updateBubbles();
			}
		}
	}
	m_bubblesOverlay->update();
	repaint();
}
*/


void BubblesBrowser::download(const QNetworkRequest &r) {
	cout << "Request to download " << qPrintable(r.url().toString()) << endl;
	stop();
	m_bubblesOverlay->downloadRequested(r.url());
	repaint();
}


void BubblesBrowser::unsupportedContent(QNetworkReply *r) {
	cout << "Request to download " << qPrintable(r->url().toString()) << endl;
	stop();
	m_bubblesOverlay->downloadRequested(r->url());
	repaint();
}


void BubblesBrowser::resizeEvent(QResizeEvent *event) {
	m_bubblesOverlay->resize(m_webView->size());
	event->accept();
}
