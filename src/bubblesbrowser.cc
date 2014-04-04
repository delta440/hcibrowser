#include "bubblesbrowser.hh"
#include "bubblesoverlay.hh"

#include <QResizeEvent>
BubblesBrowser::BubblesBrowser(QString startPage, QWidget *parent)
    : BasicBrowser(startPage, parent){
    m_bubbles = new BubblesOverlay(centralWidget());
}


void BubblesBrowser::resizeEvent(QResizeEvent *event){
    m_bubbles->resize(event->size());
    event->accept();
}
