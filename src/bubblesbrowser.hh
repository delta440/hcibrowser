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

	BubblesOverlay *m_bubblesOverlay;

public:
	BubblesBrowser(QString startPage, QWidget *parent = 0);

protected:
	void resizeEvent(QResizeEvent *event);

public slots:
	void download(const QNetworkRequest &);
	void unsupportedContent(QNetworkReply *);
};

#endif // BUBBLESBROWSER_HH
