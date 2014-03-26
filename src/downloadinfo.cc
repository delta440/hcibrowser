#include "downloadinfo.hh"
#include "download.hh"
#include <QWidget>
#include <QLabel>
#include <QProgressBar>
#include <QVBoxLayout>
#include <QHBoxLayout>
DownloadInfo::DownloadInfo(Download* download, QWidget *parent) : QWidget(parent){
    m_download = download;
    m_filename = new QLabel(m_download->fileName());

    m_amountDownloaded = new QProgressBar();
    m_amountDownloaded->setMaximum(m_download->totalKbytes());
    m_amountDownloaded->setMinimum(0);
    m_amountDownloaded->setValue(0);

    m_downloadSpeed = new QLabel("Speed: --kbps");

    connect(m_download, SIGNAL(progress(qreal,qreal)), this, SLOT(progress(qreal,qreal)));
    connect(m_download, SIGNAL(finished(bool)), this, SLOT(finished(bool)));
    QHBoxLayout *downloadInfo = new QHBoxLayout();
    downloadInfo->addWidget(m_amountDownloaded);
    downloadInfo->addWidget(m_downloadSpeed);

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(m_filename);
    layout->addLayout(downloadInfo);

    this->setLayout(layout);
}

void DownloadInfo::progress(qreal kbytes, qreal kbps){
    m_amountDownloaded->setMaximum(m_download->totalKbytes());
    m_amountDownloaded->setValue(kbytes);
    m_downloadSpeed->setText("Speed: " + QString::number(kbps) + "kbps");
}

void DownloadInfo::finished(bool okay){
    if(okay){
        disconnect(m_download, SIGNAL(progress(qreal,qreal)), this, SLOT(progress(qreal,qreal)));
        m_amountDownloaded->hide();
        m_downloadSpeed->setText("Finished");
    }
}
