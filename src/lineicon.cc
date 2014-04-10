#include "lineicon.hh"
#include <QPainter>
#include <QLinearGradient>
#include <QBrush>
#include <QPen>
#include <QRect>
#include <QImage>


LineIcon::LineIcon(int width, int height, int thickness, QObject *parent)
	: QObject(parent)
{
	m_width = width; m_height = height; m_thickness = thickness;
	m_enabled = false; m_hovering = false; m_selected = false;
	m_bgdirty = m_fgdirty = true;

	m_bgimage = new QImage(m_width, m_height,
						   QImage::Format_ARGB32_Premultiplied);
	m_fgimage = new QImage(m_width, m_height,
						   QImage::Format_ARGB32_Premultiplied);
}


void LineIcon::paintBackground(QPainter *painter) {
	if (m_bgdirty) {
		QPainter p(m_bgimage);
		p.setRenderHint(QPainter::Antialiasing);
		m_bgimage->fill(Qt::transparent);

		if (m_hovering && m_enabled) {
			QPen pen;
			pen.setWidthF(2);
			if (m_selected) {
				p.setBrush(QBrush(QColor(63,63,63)));
				pen.setColor(Qt::black);
			}
			else {
				p.setBrush(QBrush(QColor(0,0,0,0)));
				pen.setColor(Qt::black);
			}
			p.setPen(pen);
		}
		else {
			QPen pen(QColor(191,191,191));
			pen.setWidthF(0.5);
			p.setPen(pen);
			p.setBrush(QBrush(QColor(0,0,0,0)));
		}
		p.drawRoundedRect(QRect(1, 1, m_width-2, m_height-2), 5, 5);
		m_bgdirty = false;
	}

	painter->drawImage(0, 0, *m_bgimage);
}


void LineIcon::paintForeground(QPainter *painter) {
	if (m_fgdirty) {
		QPainter p(m_fgimage);
		p.setRenderHint(QPainter::Antialiasing);
		m_fgimage->fill(Qt::transparent);

		paintForegroundImp(&p);
		m_fgdirty = false;
	}

	painter->drawImage(0, 0, *m_fgimage);
}
