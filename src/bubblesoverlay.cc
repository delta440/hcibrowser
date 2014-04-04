#include "bubblesoverlay.hh"
#include <QPainter>
#include <QPen>


BubblesOverlay::BubblesOverlay(QWidget *parent):QWidget(parent){
    setPalette(Qt::transparent);
    setAttribute(Qt::WA_TransparentForMouseEvents);
}

void BubblesOverlay::paintEvent(QPaintEvent *event){
    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(QPen(Qt::red));
    painter.setBrush(QBrush(Qt::green));
    painter.drawRect(40,40, 100, 300);
}

