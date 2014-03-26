#include "linebutton.hh"
#include <QPainter>


LineButton::LineButton(LineIcon *icon, QWidget *parent) :
	QAbstractButton(parent), m_icon(icon)
{
	m_icon->setParent(this);
	setMinimumWidth(m_icon->width());
	setMinimumHeight(m_icon->height());
	setMaximumWidth(m_icon->width());
	setMaximumHeight(m_icon->height());
	m_icon->enable(true);
	m_icon->hover(false);
	m_icon->select(false);
}


void LineButton::enterEvent(QEvent *e) {
	QAbstractButton::enterEvent(e);
	m_icon->hover(true);
	repaint();
}

void LineButton::leaveEvent(QEvent *e) {
	QAbstractButton::leaveEvent(e);
	m_icon->hover(false);
	m_icon->select(false);
	repaint();
}

void LineButton::mousePressEvent(QMouseEvent *e) {
	if (m_icon->enabled()) {
		QAbstractButton::mousePressEvent(e);
		m_icon->select(true);
	}
	repaint();
}

void LineButton::mouseReleaseEvent(QMouseEvent *e) {
	if (m_icon->enabled()) {
		QAbstractButton::mouseReleaseEvent(e);
		m_icon->select(false);
	}
	repaint();
}

void LineButton::paintEvent(QPaintEvent *) {
	QPainter p(this);
	p.setRenderHint(QPainter::Antialiasing);
	m_icon->paintBackground(&p);
	m_icon->paintForeground(&p);
}
