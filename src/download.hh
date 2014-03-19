#ifndef DOWNLOAD_HH
#define DOWNLOAD_HH

#include <QObject>
#include <QString>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QFile>
#include <QTime>
class QNetworkReply;


class Download : public QObject
{
	Q_OBJECT

	qreal m_curKbytes;
	qreal m_totalKbytes;
	qreal m_speedKbps;
	QTime m_time;
	QFile m_output;
	QNetworkAccessManager m_manager;
	QNetworkReply *m_download;
	QString m_filename;

public:
	Download(const QUrl &url, QString saveDir, QObject *parent = 0);

	bool isStopped() const;

	// May return -1 if the value is unknown.
	qreal totalKbytes() const { return m_totalKbytes; }
	qreal curKbytes() const { return m_curKbytes; }

	// Returns the speed of the download, in kbytes/sec.
	qreal curSpeedKbps() const { return m_speedKbps; }

	QString fileName() const { return m_filename; }

public slots:
	void stop();

signals:
	void progress(qreal kbytes, qreal kbps);
	void started();
	void finished(bool okay);

private slots:
	void m_downloadProgress(qint64, qint64);
	void m_downloadFinished();
	void m_downloadReadyRead();
};

#endif // DOWNLOAD_HH
