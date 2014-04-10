#include "refreshicon.hh"
#include <QPainter>
#include <QPen>


RefreshIcon::RefreshIcon(int height, QObject *parent)
	: LineIcon(height, height, height/6, parent)
{ }

void RefreshIcon::paintForegroundImp(QPainter *p) {
	QPen pen;
	pen.setColor(foregroundColor());
	pen.setWidth(thickness());
	pen.setCapStyle(Qt::RoundCap);
	p->setPen(pen);

	//p->translate(width()/2.0, height()/2.0);
	//p->rotate(-25);
	//p->translate(-width()/2.0, -height()/2.0);
	p->drawArc(QRectF(1.0*width()/4, 1.0*height()/4,
					  1.0*width()/2, 1.0*height()/2),
			   0, 300*16);
	p->drawLine(QPointF(3.0*width()/4, 1.0*height()/2),
				QPointF(5.0*width()/8, 7.0*height()/16));
	p->drawLine(QPointF(3.0*width()/4, 1.0*height()/2),
				QPointF(13.0*width()/16, 6.0*height()/16));
	//p->rotate(-45);
}
