#include "bubblesoverlay.hh"
#include <QPainter>
#include <QPen>
#include <iostream> //TC

using namespace std;//TC

BubblesOverlay::BubblesOverlay(QVector<Bubble *> *bubbles, int wsize, QWidget *parent)
    :QWidget(parent), WSIZE(wsize), BSIZE(wsize/25){

    m_bubbles = bubbles;
    setPalette(Qt::transparent);
    setAttribute(Qt::WA_TransparentForMouseEvents);

}

void BubblesOverlay::paintEvent(QPaintEvent *event){
    //setup

    QPainter painter(this);
    painter.setWindow(-(WSIZE/2),-(WSIZE/2),WSIZE,WSIZE);
    painter.setRenderHint(QPainter::Antialiasing);


   //if a bubble is clicked
   bool dragging = 0; //TC
   for(QVector<Bubble*>::size_type i = 0; i < m_bubbles->size(); ++i){
       if((*m_bubbles)[i]->clicked())
           dragging = 1;
   }

   //draw the delete button
   if(dragging){
       QPen wthick;
       wthick.setColor(Qt::white);
       wthick.setWidth(BSIZE/6);
       painter.setPen(QPen(Qt::red));
       painter.setBrush(QBrush(Qt::red));
       painter.drawEllipse(
                   QRect(QPoint(-(BSIZE/2.0),(WSIZE/2.0)-BSIZE),
                         QPoint(BSIZE/2.0,(WSIZE/2.0))));
       painter.setPen(wthick);
       painter.drawLine(QPoint((-(BSIZE/2.0)) + (BSIZE/4.0),(WSIZE/2.0) - BSIZE + (BSIZE/4.0)),
                        QPoint((BSIZE/2.0) - (BSIZE/4),(WSIZE/2) - (BSIZE/4.0)));
       painter.drawLine(QPoint(((BSIZE/2.0)) - (BSIZE/4.0),(WSIZE/2.0) - BSIZE + (BSIZE/4.0)),
                        QPoint(-(BSIZE/2.0) + (BSIZE/4.0),(WSIZE/2.0) - (BSIZE/4.0)));
   }

    //temporary bubble paint
    painter.setPen(QPen(Qt::green));
    painter.setBrush(QBrush(Qt::green));
    for(QVector<Bubble*>::size_type i = 0; i < m_bubbles->size(); i++){
        painter.drawPie((*m_bubbles)[i]->getX() - (BSIZE/2.0), (*m_bubbles)[i]->getY() - (BSIZE/2.0),BSIZE, BSIZE, 0,(*m_bubbles)[i]->getAngle() * 16);
    }


}

