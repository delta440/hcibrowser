#include "bubbleswebview.hh"
#include <QMouseEvent>


BubblesWebView::BubblesWebView(QWidget *parent) :
	QWebView(parent)
{

}

void BubblesWebView::mousePressEvent(QMouseEvent *event){
	emit mousePEvent(event);
	if (!event->isAccepted())
		QWebView::mousePressEvent(event);
}

void BubblesWebView::mouseReleaseEvent(QMouseEvent *event){
	emit mouseREvent(event);
	if (!event->isAccepted())
		QWebView::mouseReleaseEvent(event);
}

void BubblesWebView::mouseMoveEvent(QMouseEvent *event){
	emit mouseMEvent(event);
	if (!event->isAccepted())
		QWebView::mouseMoveEvent(event);
}
