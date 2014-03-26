#include "downloadmanager.hh"
#include "downloadinfo.hh"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QUrl>
#include <QLabel>
#include <QPushButton>
#include <QFileDialog>
#include <QPainter>
#include <iostream>
using std::cout;
using std::endl;

DownloadManager::DownloadManager(QWidget *parent) : QWidget(parent){
	setWindowTitle("Download Manager");
	setMinimumWidth(320);
	//setMinimumHeight(240);

	m_title = new QLabel("Current Downloads:");
	m_hideBtn = new QPushButton("Hide");
	m_clearBtn = new QPushButton("Clear List");

	m_downloadArea = new QVBoxLayout();
	m_downloadArea->addStretch();

	connect(m_hideBtn, SIGNAL(clicked()), this, SLOT(hide()));
	connect(m_clearBtn, SIGNAL(clicked()), this, SLOT(clearList()));

	QHBoxLayout *bottom = new QHBoxLayout();
	bottom->addWidget(m_clearBtn);
	bottom->addWidget(m_hideBtn);

	QVBoxLayout *layout = new QVBoxLayout();
	layout->addWidget(m_title);
	layout->addLayout(m_downloadArea);
	layout->addLayout(bottom);

	this->setLayout(layout);
}

void DownloadManager::downloadRequested(const QUrl &url){
	QString path = url.path();
	QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), QFileInfo(path).fileName());
	if (fileName.size() == 0) return;

	cout << "Filename = " << qPrintable(fileName) << endl;

	m_downloads.push_front(new Download(url, fileName));
	m_downloadInfos.push_front(new DownloadInfo(m_downloads.front()));
	m_downloadArea->insertWidget(0, m_downloadInfos.front());
	connect(m_downloads.front(), SIGNAL(progress(qreal,qreal)), this, SLOT(updateProgress()));
	connect(m_downloads.front(), SIGNAL(finished(bool)), this, SLOT(updateProgress()));

	this->show();
}


void DownloadManager::clearList() {
	for (int i = m_downloads.size()-1; i >= 0; --i) {
		if (m_downloads[i]->isStopped()) {
			disconnect(m_downloads[i], SIGNAL(progress(qreal,qreal)), this, SLOT(updateProgress()));
			disconnect(m_downloads[i], SIGNAL(finished(bool)), this, SLOT(updateProgress()));
			m_downloadArea->removeWidget(m_downloadInfos[i]);
			delete m_downloadInfos[i];
			m_downloadInfos.removeAt(i);
			delete m_downloads[i];
			m_downloads.removeAt(i);
		}
	}
	updateGeometry();
	repaint();
}


void DownloadManager::updateProgress() {
	qreal total = 0, cnt = 0;
	for (int i = 0; i < m_downloadInfos.size(); ++i) {
		if (m_downloadInfos[i]->isFinished()) continue;
		total += m_downloadInfos[i]->progress();
		cnt++;
	}
	if (cnt != 0)
		emit totalProgress(total/cnt);
	else
		emit totalProgress(0);
}
