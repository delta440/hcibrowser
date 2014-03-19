#include "addressbar.hh"
#include <QPaintEvent>
#include <QPainter>
#include <QProgressBar>


AddressBar::AddressBar(QWidget *parent) :
	QLineEdit(parent)
{
	m_progress = -1;
}


void AddressBar::paintEvent(QPaintEvent *e) {
	QLineEdit::paintEvent(e);
	if (m_progress > 0 && m_progress <= 100) {
		QPainter p(this);
		p.setPen(Qt::blue);
		p.drawLine(0, height()-1, (qreal)width()*m_progress / 100.0, height()-1);
	}
}


void AddressBar::setProgress(int value) {
	m_progress = value;
	repaint();
}
