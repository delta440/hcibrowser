#ifndef BUBBLESBROWSER_HH
#define BUBBLESBROWSER_HH
#include "basicbrowser.hh"


class BubblesBrowser : public BasicBrowser {
    Q_OBJECT

    public:
    explicit BubblesBrowser(QString startPage, QWidget *parent = 0);

    protected:
    void paintEvent(QPaintEvent *);


};



#endif // BUBBLESBROWSER_HH
