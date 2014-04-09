#include "downloadinfo.hh"
#include "download.hh"
#include "linebutton.hh"
#include "stopicon.hh"
#include <QWidget>
#include <QLabel>
#include <QProgressBar>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPainter>


DownloadInfo::DownloadInfo(Download* download, QWidget *parent) : QWidget(parent){
	m_download = download;
	m_filename = new QLabel(m_download->fileName());
	m_progress = 0;

	m_amountDownloaded = new QProgressBar();
	m_amountDownloaded->setMaximum(m_download->totalKbytes());
	m_amountDownloaded->setMinimum(0);
	m_amountDownloaded->setValue(0);
	//m_amountDownloaded->setMinimumWidth(1.0*width()/2);

	m_downloadSpeed = new QLabel("-- kbps");
	m_downloadSpeed->setMinimumWidth(75);
	m_downloadSpeed->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
	m_cancelBtn = new LineButton(new StopIcon(35));

	connect(m_download, SIGNAL(progress(qreal,qreal)), this, SLOT(progress(qreal,qreal)));
	connect(m_download, SIGNAL(finished(bool)), this, SLOT(finished(bool)));
	connect(m_cancelBtn, SIGNAL(clicked()), this, SLOT(cancel()));

	QHBoxLayout *downloadInfo = new QHBoxLayout();
	downloadInfo->addWidget(m_amountDownloaded, 1);
	//downloadInfo->addSpacing(5);
	downloadInfo->addWidget(m_downloadSpeed, 0, Qt::AlignRight);

	QVBoxLayout *layout = new QVBoxLayout();
	m_filename->setMaximumWidth(350);
	m_filename->setMinimumWidth(350);
	layout->addWidget(m_filename);
	layout->addLayout(downloadInfo);

	QHBoxLayout *withButton = new QHBoxLayout();
	withButton->setContentsMargins(10,10,10,10);
	withButton->addLayout(layout);
	withButton->addStretch();
	withButton->addWidget(m_cancelBtn, 0, Qt::AlignRight);

	this->setLayout(withButton);
	//this->setStyleSheet("border: 1px solid black");
}


void DownloadInfo::progress(qreal kbytes, qreal kbps){
	m_amountDownloaded->setMaximum(m_download->totalKbytes());
	m_amountDownloaded->setValue(kbytes);
	QString speed = QString::number(kbps,'f',1) + " kbps";
	if (kbps >= 1024)
		speed = QString::number(kbps/1024, 'f', 1) + " Mbps";
	m_downloadSpeed->setText(speed);

	m_progress = 100*kbytes / m_download->totalKbytes();
}


void DownloadInfo::finished(bool okay){
	if (okay) m_downloadSpeed->setText("Download Complete.");
	else m_downloadSpeed->setText("Download Failed.");

	disconnect(m_download, SIGNAL(progress(qreal,qreal)), this, SLOT(progress(qreal,qreal)));
	m_amountDownloaded->hide();
	m_cancelBtn->hide();
}


void DownloadInfo::cancel() {
	disconnect(m_download, SIGNAL(progress(qreal,qreal)), this, SLOT(progress(qreal,qreal)));
	m_download->stop();
	m_amountDownloaded->hide();
	m_downloadSpeed->setText("Download Canceled.");
	m_cancelBtn->hide();
}


void DownloadInfo::paintEvent(QPaintEvent *e) {
	QPainter p(this);
	p.setRenderHint(QPainter::Antialiasing);
	p.setBrush(QColor(255,255,255));
	p.drawRoundedRect(QRect(0,0,width()-1, height()-1), 5, 5);

	QWidget::paintEvent(e);
}
