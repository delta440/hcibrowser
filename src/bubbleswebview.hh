#ifndef BUBBLESWEBVIEW_HH
#define BUBBLESWEBVIEW_HH

#include <QWebView>

class BubblesWebView : public QWebView
{
	Q_OBJECT
public:
	explicit BubblesWebView(QWidget *parent = 0);

signals:
	void mousePEvent(QMouseEvent * event);
	void mouseMEvent(QMouseEvent * event);
	void mouseREvent(QMouseEvent * event);
protected:
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
};

#endif // BUBBLESWEBVIEW_HH
