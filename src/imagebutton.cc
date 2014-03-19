#include "imagebutton.hh"
#include <QIcon>
#include <QPixmap>
#include <QBitmap>
#include <QPaintEvent>
#include <QPainter>
#include <stdexcept>
using namespace std;


ImageButton::ImageButton(
		QString normalIcon, QString hoverIcon,
		QString pressedIcon, QWidget *parent)
	: QAbstractButton(parent)
{
	QPixmap normalImg(normalIcon);
	QPixmap hoverImg(hoverIcon);
	QPixmap pressedImg(pressedIcon);
	//QPixmap disabledImg(disabledIcon);

	if (normalImg.isNull())
		throw runtime_error(string("unable to load ") + normalIcon.toStdString());
	if (hoverImg.isNull())
		throw runtime_error(string("unable to load ") + hoverIcon.toStdString());
	if (pressedImg.isNull())
		throw runtime_error(string("unable to load ") + pressedIcon.toStdString());

	//normalImg.setMask(mask);
	//hoverImg.setMask(mask);
	//pressedImg.setMask(mask);
	//disabledImg.setMask(mask);

	m_normalIcon = new QIcon(normalImg);
	m_hoverIcon = new QIcon(hoverImg);
	m_pressedIcon = new QIcon(hoverImg);
	//m_disabledIcon = new QIcon(disabledImg);
	m_state = 0;
	//m_disabled = false;

	setMinimumWidth(normalImg.width());
	setMinimumHeight(normalImg.height());
	setMaximumWidth(normalImg.width());
	setMaximumHeight(normalImg.height());
}


void ImageButton::enterEvent(QEvent *e) {
	QAbstractButton::enterEvent(e);
	m_state = 1;
}


void ImageButton::leaveEvent(QEvent *e) {
	QAbstractButton::leaveEvent(e);
	m_state = 0;
}


void ImageButton::mousePressEvent(QMouseEvent *e) {
	QAbstractButton::mousePressEvent(e);
	m_state = 2;
}


void ImageButton::mouseReleaseEvent(QMouseEvent *e) {
	QAbstractButton::mouseReleaseEvent(e);
	// We might get this event if the user leaves the widget, so only
	// do something if the user hasn't left yet.
	if (m_state == 2) {
		m_state = 1;
	}
}


void ImageButton::paintEvent(QPaintEvent *e) {
	QPainter p(this);
	if (m_state == 0)
		m_normalIcon->paint(&p, 0, 0, width(), height());
	else if (m_state == 1)
		m_hoverIcon->paint(&p, 0, 0, width(), height());
	else
		m_pressedIcon->paint(&p, 0, 0, width(), height());
}
