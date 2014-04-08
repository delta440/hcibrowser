#ifndef BUBBLESOVERLAY_HH
#define BUBBLESOVERLAY_HH

#include "bubble.hh"

#include <QMouseEvent>
#include <QWidget>
#include <QVector>
#include <iostream>//TC
using namespace std;//TC

class BubblesOverlay : public QWidget
{
    Q_OBJECT
public:
    explicit BubblesOverlay(QVector<Bubble*>* bubbles, int wsize, QWidget *parent);

protected:
    void paintEvent(QPaintEvent *event);

private:
    QVector<Bubble*>* m_bubbles;
    const int WSIZE, BSIZE;
};

#endif // BUBBLESOVERLAY_HH
