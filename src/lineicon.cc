#include "lineicon.hh"
#include <QPainter>
#include <QLinearGradient>
#include <QBrush>
#include <QPen>
#include <QRect>


LineIcon::LineIcon(int width, int height, int thickness, QObject *parent)
	: QObject(parent)
{
	m_width = width; m_height = height; m_thickness = thickness;
	m_enabled = false; m_hovering = false; m_selected = false;
}


void LineIcon::paintBackground(QPainter *p) {
	if (m_hovering && m_enabled) {
		QPen pen;
		pen.setWidthF(2);
		if (m_selected) {
			p->setBrush(QBrush(QColor(63,63,63)));
			pen.setColor(Qt::black);
		}
		else {
			p->setBrush(QBrush(QColor(0,0,0,0)));
			pen.setColor(Qt::black);
		}
		p->setPen(pen);
	}
	else {
		QPen pen(QColor(191,191,191));
		pen.setWidthF(0.5);
		p->setPen(pen);
		p->setBrush(QBrush(QColor(0,0,0,0)));
	}
	p->drawRoundedRect(QRect(1, 1, m_width-2, m_height-2), 5, 5);
}
