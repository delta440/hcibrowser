#ifndef DOWNLOADMANAGER_HH
#define DOWNLOADMANAGER_HH

#include <QWidget>
#include "download.hh"
#include "downloadinfo.hh"
class QUrl;
class QPushButton;
class QLabel;
class QVBoxLayout;


class DownloadManager : public QWidget {
	Q_OBJECT
public:
	DownloadManager(QWidget *parent = 0);

public slots:
	void downloadRequested(const QUrl &url);
	void clearList();
	void updateProgress();

signals:
	void totalProgress(int percent);

protected:
	//void paintEvent(QPaintEvent *event);

private:
	QVBoxLayout *m_downloadArea;
	QPushButton *m_hideBtn;
	QPushButton *m_clearBtn;
	QLabel *m_title;
	QVector<DownloadInfo*> m_downloadInfos;
	QVector<Download*> m_downloads;

};






#endif // DOWNLOADMANAGER_HH
