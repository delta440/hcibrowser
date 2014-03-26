#include "downloadsbutton.hh"
#include "downloadsicon.hh"
#include <QPainter>
#include <QPen>


DownloadsButton::DownloadsButton(int height, QWidget *parent) :
	LineButton(new DownloadsIcon(height), parent)
{ }

void DownloadsButton::setProgress(int progress) {
	m_progress = progress;
	repaint();
}

void DownloadsButton::paintEvent(QPaintEvent *) {
	QPainter p(this);
	p.setRenderHint(QPainter::Antialiasing);
	m_icon->paintBackground(&p);
	if (m_progress >= 0 && m_progress < 100) {
		p.translate(0.1*width(), 0.1*height());
		DownloadsIcon::paintProgressWheel(&p, 0.8*width(), m_progress);
		p.translate(-0.1*width(), -0.1*height());
	}
	m_icon->paintForeground(&p);
}
