#ifndef BUBBLESBROWSER_HH
#define BUBBLESBROWSER_HH

#include "basicbrowser.hh"

class BubblesOverlay;
class QResizeEvent;

class BubblesBrowser : public BasicBrowser
{
    Q_OBJECT

    BubblesOverlay *m_bubbles;

public:
    BubblesBrowser(QString startPage, QWidget *parent = 0);

protected:
    void resizeEvent(QResizeEvent *event);
};

#endif // BUBBLESBROWSER_HH
