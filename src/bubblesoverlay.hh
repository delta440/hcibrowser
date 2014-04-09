#ifndef BUBBLESOVERLAY_HH
#define BUBBLESOVERLAY_HH

#include "bubble.hh"

#include <QMouseEvent>
#include <QWidget>
#include <QVector>
#include <QTimer>
#include <iostream>//TC
using namespace std;//TC

class BubblesOverlay : public QWidget
{
	Q_OBJECT
public:
	explicit BubblesOverlay(QWidget *parent);

public slots:
	void mouseMEvent(QMouseEvent * event);
	void mousePEvent(QMouseEvent * event);
	void mouseREvent(QMouseEvent *event);
	void downloadRequested(const QUrl& url);

protected:
	void paintEvent(QPaintEvent *event);
	void resizeEvent(QResizeEvent *event);

private slots:
	void timeUp();

private:
	QVector<Bubble*> m_bubbles;
	QRectF m_deleteButton;
	int m_mousex, m_mousey;
	QTimer m_timer;

	void updateBubbles();
};

#endif // BUBBLESOVERLAY_HH
