#ifndef DOWNLOADINFO_H
#define DOWNLOADINFO_H

#include <QWidget>
#include "download.hh"
class QLabel;
class QProgressBar;
class QAbstractButton;
class QPaintEvent;


class DownloadInfo : public QWidget {
	Q_OBJECT
public:
	DownloadInfo(Download *download, QWidget *parent = 0);

	bool isFinished() const { return m_download->isStopped(); }
	int progress() const { return m_progress; }

public slots:
	void progress(qreal kbytes, qreal kbps);
	void finished(bool okay);
	void cancel();

protected:
	void paintEvent(QPaintEvent *);

private:
	QLabel *m_filename;
	QLabel *m_downloadSpeed;
	QProgressBar *m_amountDownloaded;
	QAbstractButton *m_cancelBtn;
	Download *m_download;
	int m_progress;

};



#endif // DOWNLOADINFO_H
