#ifndef BUBBLESBROWSER_HH
#define BUBBLESBROWSER_HH

#include "basicbrowser.hh"
#include "bubble.hh"

#include <QVector>

class BubblesOverlay;
class QResizeEvent;

class BubblesBrowser : public BasicBrowser
{
    Q_OBJECT
private:
    BubblesOverlay *m_bubblesOverlay;
    QVector<Bubble*> m_bubbles;
    int m_mousex;
    int m_mousey;
    //width/height in pixels of the drawn window
    const int WSIZE, BSIZE;

    //used to convert to setwindow coordinates
    int convxToWindow(int x);
    int convyToWindow(int y);
    //determins if bubbles are overlapping
    //if only b1 is given checks if over delete button
    bool overlapping(Bubble *b1, Bubble *b2 = NULL, int tol = 50);

    //function to handle moving the bubbles
    void updateBubbles();

public:
    BubblesBrowser(QString startPage, int wsize, QWidget *parent = 0);

protected:
    void resizeEvent(QResizeEvent *event);


public slots:
    void mouseMEvent(QMouseEvent * event);
    void mousePEvent(QMouseEvent * event);
    void mouseREvent(QMouseEvent *event);
    void download(const QNetworkRequest &);
    void unsupportedContent(QNetworkReply *);
};

#endif // BUBBLESBROWSER_HH
