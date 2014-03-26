#include "backicon.hh"
#include <QPainter>
#include <QPen>


BackIcon::BackIcon(int height, QObject *parent)
	: LineIcon(1.1*height, height, height/6, parent)
{ }

void BackIcon::paintForeground(QPainter *p) {
	QPen pen;
	pen.setColor(foregroundColor());
	pen.setWidth(thickness());
	pen.setCapStyle(Qt::RoundCap);
	p->setPen(pen);

	p->drawLine(QPointF(1.0*width()/4, 1.0*height()/2),
				QPointF(3.0*width()/4, 1.0*height()/2));
	p->drawLine(QPointF(1.0*width()/4, 1.0*height()/2),
				QPointF(1.0*width()/2, 1.0*height()/4));
	p->drawLine(QPointF(1.0*width()/4, 1.0*height()/2),
				QPointF(1.0*width()/2, 3.0*height()/4));
}
