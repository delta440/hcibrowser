#include "bubbleswebview.hh"

BubblesWebView::BubblesWebView(QWidget *parent) :
    QWebView(parent){

}

void BubblesWebView::mousePressEvent(QMouseEvent *event){
    emit mousePEvent(event);
    QWebView::mousePressEvent(event);
}

void BubblesWebView::mouseReleaseEvent(QMouseEvent *event){
    emit mouseREvent(event);
    QWebView::mouseReleaseEvent(event);
}

void BubblesWebView::mouseMoveEvent(QMouseEvent *event){
    emit mouseMEvent(event);
    QWebView::mouseMoveEvent(event);
}
