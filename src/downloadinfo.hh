#ifndef DOWNLOADINFO_H
#define DOWNLOADINFO_H

#include <QWidget>

class Download;
class QLabel;
class QProgressBar;

class DownloadInfo : public QWidget {

    Q_OBJECT

public:
    DownloadInfo(Download *download, QWidget *parent = 0);
public slots:
    void progress(qreal kbytes, qreal kbps);
    void finished(bool okay);
protected:

private:
    QLabel *m_filename;
    QLabel *m_downloadSpeed;
    QProgressBar *m_amountDownloaded;
    Download *m_download;

};



#endif // DOWNLOADINFO_H
