#include "basicbrowser.hh"
#include "addressbar.hh"
#include "imagebutton.hh"
#include "downloadmanager.hh"
#include <QWebView>
#include <QUrl>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QProgressBar>
#include <QIcon>
#include <QBitmap>
#include <QPixmap>
#include <QNetworkReply>
#include <iostream>
#include <cctype>
using namespace std;


static const QString NAME = "BasicBrowser";


BasicBrowser::BasicBrowser(QString startPage, QWidget *parent)
  : QMainWindow(parent)
{
	// Create the buttons.

	m_backBtn = new ImageButton(
				"resources/back.png", "resources/back_h.png",
				"resources/back_p.png");
	m_forwardBtn = new ImageButton(
				"resources/forward.png", "resources/forward_h.png",
				"resources/forward_p.png");
	m_goBtn = new ImageButton(
				"resources/go.png", "resources/go_h.png",
				"resources/go_p.png");
	m_stopBtn = new ImageButton(
				"resources/stop.png", "resources/stop_h.png",
				"resources/stop_p.png");
	m_refreshBtn = new ImageButton(
				"resources/reload.png", "resources/reload_h.png",
				"resources/reload_p.png");
    m_downloadsBtn = new ImageButton(
                "resources/downloads.png", "resources/downloads_h.png",
                "resources/downloads_p.png");
	m_addressBar = new AddressBar;
    m_downloadManager = new DownloadManager();
	m_webView = new QWebView;

	// The address bar needs a bit of tweaking ...
	m_addressBar->setMinimumHeight(m_goBtn->height()-2);
	m_addressBar->setFont(QFont("Arial", 12));
	m_addressBar->setText(startPage);
	m_address = startPage;

	// ... as does the web view, if we want to catch download events ...
	m_webView->page()->setForwardUnsupportedContent(true);

	// Set up the layout.
	m_barLayout = new QHBoxLayout;
	m_barLayout->setContentsMargins(5,5,5,5);
	m_barLayout->addWidget(m_backBtn, 0, Qt::AlignVCenter);
	m_barLayout->addWidget(m_forwardBtn, 0, Qt::AlignVCenter);
	m_barLayout->addSpacing(5);
	m_barLayout->addWidget(m_addressBar, 1, Qt::AlignVCenter);
	m_barLayout->addWidget(m_goBtn, 0, Qt::AlignVCenter);
	m_barLayout->addWidget(m_stopBtn, 0, Qt::AlignVCenter);
	m_barLayout->addSpacing(5);
	m_barLayout->addWidget(m_refreshBtn, 0, Qt::AlignRight|Qt::AlignVCenter);
    addBarButton(m_downloadsBtn);
	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->setContentsMargins(0,0,0,0);
	mainLayout->setSpacing(0);
	mainLayout->addLayout(m_barLayout);
	mainLayout->addWidget(m_webView, 1);

	QWidget *window = new QWidget;
	window->setLayout(mainLayout);
	setCentralWidget(window);

	// Connect things together.
	connect(m_webView, SIGNAL(loadStarted()),
			this, SLOT(loadStarted()));
	connect(m_webView, SIGNAL(loadProgress(int)),
			this, SLOT(loadProgress(int)));
	connect(m_webView, SIGNAL(loadFinished(bool)),
			this, SLOT(loadFinished(bool)));
	connect(m_backBtn, SIGNAL(clicked()),
			m_webView, SLOT(back()));
	connect(m_forwardBtn, SIGNAL(clicked()),
			m_webView, SLOT(forward()));
	connect(m_goBtn, SIGNAL(clicked()),
			this, SLOT(go()));
	connect(m_stopBtn, SIGNAL(clicked()),
			this, SLOT(stop()));
	connect(m_refreshBtn, SIGNAL(clicked()),
			m_webView, SLOT(reload()));
	connect(m_addressBar, SIGNAL(returnPressed()),
			this, SLOT(go()));
	connect(m_webView->page(), SIGNAL(downloadRequested(QNetworkRequest)),
			this, SLOT(download(QNetworkRequest)));
	connect(m_webView->page(), SIGNAL(unsupportedContent(QNetworkReply*)),
			this, SLOT(unsupportedContent(QNetworkReply*)));
    connect(this, SIGNAL(downloadRequested(QUrl)), m_downloadManager,
            SLOT(downloadRequested(QUrl)));
    connect(m_downloadsBtn, SIGNAL(clicked()), m_downloadManager, SLOT(show()));

	// Start loading the default page.
	m_webView->load(QUrl(startPage));
	setWindowTitle(NAME);
}


BasicBrowser::~BasicBrowser() { }


void BasicBrowser::addBarButton(QAbstractButton *btn) {
	m_barLayout->addSpacing(5);
	m_barLayout->addWidget(btn, 0, Qt::AlignVCenter);
	repaint();
}


void BasicBrowser::go() {
	QString address = m_addressBar->text();
	m_triedGoogle = false;
	// If the address contains spaces, treat it as a goole query.
	if (address.contains(' ')) {
		m_address = address;
		loadFinished(false);
	}
	else {
		// If we didn't get a protocol, default to http.
		if (!address.contains("://"))
			address.prepend("http://");
		cout << "Loading " << address.toStdString() << " ...\n";
		m_address = address;
		m_webView->load(address);
	}
}


void BasicBrowser::stop() {
	m_webView->stop();
	m_stopBtn->setVisible(false);
	m_goBtn->setVisible(true);
	m_addressBar->setProgress(-1);
	m_triedGoogle = true;
}


void BasicBrowser::loadStarted() {
   //setWindowTitle("Loading ...");
	m_goBtn->setVisible(false);
	m_stopBtn->setVisible(true);
	m_addressBar->setProgress(0);
	m_address = m_addressBar->text();
}


void BasicBrowser::loadProgress(int progress) {
   setWindowTitle(m_webView->title() + " - " + NAME);
   if (progress >= 25)
	   m_addressBar->setText(m_webView->url().toString());
   m_addressBar->setProgress(progress);
}


void BasicBrowser::loadFinished(bool okay) {
   if (okay) {
	   setWindowTitle(m_webView->title() + " - " + NAME);
	   m_addressBar->setText(m_webView->url().toString());
	   m_addressBar->setProgress(-1);
	   m_stopBtn->setVisible(false);
	   m_goBtn->setVisible(true);
   }
   else if (!m_triedGoogle){
	   m_triedGoogle = true;
	   QString query = "https://www.google.ca/search?q=";
	   QString param = m_address;
	   // Note that this is only safe for ascii characters!
	   param.replace('%', "%25");
	   for (int i = 0; i < 128; ++i) {
		   if (!isalnum(i) && i != '%' && i != ' ')
			   param.replace(QChar((char)i), QString("%%1").arg(i,2,16));
	   }
	   param.replace(' ', '+');
	   query.append(param);
	   cout << "Searching " << param.toStdString() << " on Google ...\n";
	   m_webView->load(QUrl(query));
   } else {
	   QString failurePage = tr(
			   "<html>\n"
			   "<head><title>Page not found</title></head>\n"
			   "<body>\n"
			   "<h2>Awww snap :(</h2>\n"
			   "<p>Something went wrong while loading '%1'. "
			   "Check the address and try to reload it.</p>\n"
			   "</body>\n"
			   "</html>\n").arg(m_address);
	   m_webView->setHtml(failurePage);
   }
   repaint();
}


void BasicBrowser::download(const QNetworkRequest &r) {
	cout << "Request to download " << qPrintable(r.url().toString()) << endl;
	stop();
	emit downloadRequested(r.url());
	//XXX
    //new Download(r.url(), "./");
}


void BasicBrowser::unsupportedContent(QNetworkReply *r) {
	cout << "Request to download " << qPrintable(r->url().toString()) << endl;
	stop();
	emit downloadRequested(r->url());
	//XXX
	//new Download(r->url(), "./");
}
