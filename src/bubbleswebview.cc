#include "bubbleswebview.hh"
#include <QMouseEvent>
#include <QScroller>


BubblesWebView::BubblesWebView(QWidget *parent) :
	QWebView(parent), m_mousePressed(false)
{
	// Trick to get kinetic scrolling to work correctly. See
	// http://doc.qt.digia.com/qt-maemo-4.6/maemo5-webview.html
	//installEventFilter(this);

	//QScroller::grabGesture(this, QScroller::LeftMouseButtonGesture);
}

void BubblesWebView::mousePressEvent(QMouseEvent *event){
	event->ignore();
	emit mousePEvent(event);
	if (!event->isAccepted())
		QWebView::mousePressEvent(event);
}

void BubblesWebView::mouseReleaseEvent(QMouseEvent *event){
	event->ignore();
	emit mouseREvent(event);
	if (!event->isAccepted())
		QWebView::mouseReleaseEvent(event);
}

void BubblesWebView::mouseMoveEvent(QMouseEvent *event){
	event->ignore();
	emit mouseMEvent(event);
	if (!event->isAccepted())
		QWebView::mouseMoveEvent(event);
}

bool BubblesWebView::eventFilter(QObject *, QEvent *e) {
	switch (e->type()) {
	case QEvent::MouseButtonPress:
	case QEvent::MouseButtonRelease:
	{
		QMouseEvent *me = static_cast<QMouseEvent*>(e);
		if (me->button() == Qt::LeftButton)
			m_mousePressed = e->type() == QEvent::MouseButtonPress;
		return false;
	}
	case QEvent::MouseMove:
		return m_mousePressed;
	default:
		return false;
	}
}
