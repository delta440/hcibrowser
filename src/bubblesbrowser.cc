#include "bubblesbrowser.hh"
#include <QPainter>
#include <QWebView>
BubblesBrowser::BubblesBrowser(QString startPage, QWidget *parent):BasicBrowser(startPage, parent){

}


void BubblesBrowser::paintEvent(QPaintEvent * event){
BasicBrowser::paintEvent(event);



QPainter painter(this);

painter.setRenderHint(QPainter::Antialiasing, true);
painter.setWindow(-50, -50, 100, 100);

painter.setBrush(QBrush(Qt::green));
//painter.drawPie(0,0,200,200,0,200);

painter.drawRect(-50,-50,50,50);

}
