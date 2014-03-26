#ifndef DOWNLOADMANAGER_HH
#define DOWNLOADMANAGER_HH

#include <QWidget>
#include "download.hh"
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
protected:
    void paintEvent(QPaintEvent *event);
private:
    QVBoxLayout *m_downloadArea;
    QPushButton *m_hideBtn;
    QLabel *m_title;
    QVector<Download*> m_downloads;

};






#endif // DOWNLOADMANAGER_HH
