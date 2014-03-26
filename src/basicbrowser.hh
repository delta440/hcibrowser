#ifndef BASIC_BROWSER_HH
#define BASIC_BROWSER_HH

#include <QMainWindow>
#include <QString>
#include <QNetworkRequest>
class QWebView;
class QUrl;
class ImageButton;
class AddressBar;
class QAbstractButton;
class QHBoxLayout;
class QNetworkReply;
class DownloadManager;


/**
 * @brief The BasicBrowser class
 *
 * This implements a basic web browser interface. It has buttons for
 * back, forward, reload, and go/stop. The address bar can be used
 * for Google queries, in addition to specifying the webpage.
 *
 * Additional buttons can be added to the bar using the addBarButton()
 * method. This class does not handle downloads; those need to be
 * dealt with somehow using the provided signal. This signal is fired
 * whenever the user clicks on a link and the browser can't handle the
 * request internally (or the user right clicks and selects "Save as").
 */
class BasicBrowser : public QMainWindow {
	Q_OBJECT

	QWebView *m_webView;
	ImageButton *m_backBtn;
	ImageButton *m_forwardBtn;
	ImageButton *m_goBtn;
	ImageButton *m_stopBtn;
	ImageButton *m_refreshBtn;
    ImageButton *m_downloadsBtn;
	AddressBar *m_addressBar;
	QHBoxLayout *m_barLayout;
    DownloadManager *m_downloadManager;
	QString m_address;
	bool m_triedGoogle;

public:
	explicit BasicBrowser(QString startPage, QWidget *parent = 0);
	virtual ~BasicBrowser();

	void addBarButton(QAbstractButton *);

public slots:
	void go();
	void stop();
	void loadStarted();
	void loadFinished(bool okay);
	void loadProgress(int progress);
	void download(const QNetworkRequest &);
	void unsupportedContent(QNetworkReply *);

signals:
	void downloadRequested(const QUrl& url);
};

#endif
