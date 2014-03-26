#include "download.hh"
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QFileInfo>
#include <QIODevice>
#include <stdexcept>
#include <iostream>
#include <iomanip>
using namespace std;


Download::Download(const QUrl &url, QString saveDir, QObject *parent)
	: QObject(parent), m_curKbytes(0), m_totalKbytes(-1), m_speedKbps(0)
{
	QString path = url.path();
	m_filename = QFileInfo(path).fileName();

	if (m_filename.isEmpty())
		m_filename = "download.unknown";

	// Don't overwrite anything - come up with a unique filename by
	// appending ".#" to the filename.
	if (QFile::exists(m_filename)) {
		int i = 0;
		m_filename += '.';
		while (QFile::exists(m_filename + QString::number(i))) ++i;
		m_filename += QString::number(i);
	}

	m_output.setFileName(saveDir);// + "/" + m_filename);
	// Open the output file. If we can't, then throw an exception.
	if (!m_output.open(QIODevice::WriteOnly)) {
	   cerr << "Couldn't open " << qPrintable(saveDir) // + "/" + m_filename)
		<< " - " << qPrintable(m_output.errorString());
	   throw runtime_error(qPrintable(m_output.errorString()));
	}

	// Create the network request.
	QNetworkRequest request(url);
	m_download = m_manager.get(request);

	// Connect our download to the appropriate slots.
	connect(m_download, SIGNAL(downloadProgress(qint64,qint64)),
			this, SLOT(m_downloadProgress(qint64,qint64)));
	connect(m_download, SIGNAL(finished()),
			this, SLOT(m_downloadFinished()));
	connect(m_download, SIGNAL(readyRead()),
			this, SLOT(m_downloadReadyRead()));

	cout << "Downloading " << qPrintable(url.toString()) << " ...\n";
	m_time.start();
	emit started();
}


bool Download::isStopped() const {
	return m_download == 0 || !m_download->isRunning() || !m_output.isOpen();
}


void Download::stop() {
	if (m_download)
		m_download->abort();
}


void Download::m_downloadProgress(qint64 recv, qint64 total) {
	m_totalKbytes = (qreal)total / 1024.0;
	m_curKbytes = (qreal)recv / 1024.0;
	m_speedKbps = m_curKbytes * 1000.0 / m_time.elapsed();
	//XXX
	cout << qPrintable(m_filename) << ": "
		 << fixed << setprecision(1)
		 << m_curKbytes << "kb / " << m_totalKbytes << "kb (" << m_speedKbps << "kb/s)\n";

	emit progress(m_curKbytes, m_speedKbps);
}


void Download::m_downloadFinished() {
	m_output.close();
	//XXX
	cout << "Finished downloading " << qPrintable(m_filename) << endl;

	emit finished(!m_download->error());
	m_download->deleteLater();
	m_download = 0;
}


void Download::m_downloadReadyRead() {
	m_output.write(m_download->readAll());
}
