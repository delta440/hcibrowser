#include "stopicon.hh"
#include <QPainter>
#include <QPen>


StopIcon::StopIcon(int height, QObject *parent)
	: LineIcon(height, height, height/6, parent)
{ }

void StopIcon::paintForeground(QPainter *p) {
	QPen pen;
	pen.setColor(foregroundColor());
	pen.setWidth(thickness());
	pen.setCapStyle(Qt::RoundCap);
	p->setPen(pen);

	p->drawLine(QPointF(1.0*width()/3, 1.0*height()/3),
				QPointF(2.0*width()/3, 2.0*height()/3));
	p->drawLine(QPointF(1.0*width()/3, 2.0*height()/3),
				QPointF(2.0*width()/3, 1.0*height()/3));
}
