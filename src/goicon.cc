#include "goicon.hh"
#include <QPainter>
#include <QPen>


GoIcon::GoIcon(int height, QObject *parent)
	: LineIcon(height, height, height/6, parent)
{ }

void GoIcon::paintForeground(QPainter *p) {
	QPen pen;
	pen.setColor(foregroundColor());
	pen.setWidth(thickness());
	//pen.setCapStyle(Qt::RoundCap);
	pen.setJoinStyle(Qt::MiterJoin);
	p->setPen(pen);
	p->setBrush(QBrush(foregroundColor()));

	QPointF points[] = {
		QPointF(2.0*width()/3, 1.0*height()/2),
		QPointF(1.0*width()/3, 1.0*height()/3),
		QPointF(1.0*width()/3, 2.0*height()/3)
	};

	p->drawConvexPolygon(points, 3);
}
