#ifndef BUBBLESOVERLAY_HH
#define BUBBLESOVERLAY_HH

#include <QWidget>

class BubblesOverlay : public QWidget
{
    Q_OBJECT
public:
    explicit BubblesOverlay(QWidget *parent);

protected:
    void paintEvent(QPaintEvent *event);

};

#endif // BUBBLESOVERLAY_HH
