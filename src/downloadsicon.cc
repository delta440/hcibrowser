#include "downloadsicon.hh"
#include <QPainter>
#include <QPen>


DownloadsIcon::DownloadsIcon(int height, QObject *parent)
	: LineIcon(height, height, height/6, parent)
{ }

void DownloadsIcon::paintForegroundImp(QPainter *p) {
	p->save();

	QPen pen;
	pen.setColor(foregroundColor());
	pen.setJoinStyle(Qt::MiterJoin);
	pen.setWidth(thickness());
	p->setPen(pen);
	p->setBrush(Qt::black);

	// Draw bottom arrow.
	QPointF points[] = {
		QPointF(1.0*width()/3, 1.0*height()/2),
		QPointF(2.0*width()/3, 1.0*height()/2),
		QPointF(1.0*width()/2, 2.0*height()/3)
	};
	p->drawConvexPolygon(points, 3);

	pen.setWidth(thickness()*2);
	p->setPen(pen);
	p->drawLine(QPointF(1.0*width()/2, 1.0*height()/3),
				QPointF(1.0*width()/2, 1.0*height()/2));

	p->restore();
}

void DownloadsIcon::paintProgressWheel(QPainter *p, qreal size, int progress) {
	p->save();

	QColor colour(0,255,0,120);
	QRectF rect(0,0, size, size);

	p->setPen(Qt::NoPen);
	p->setBrush(colour);
	p->drawPie(rect, 90*16, -3.6*16*progress);

	p->restore();
}
