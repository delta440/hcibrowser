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
	
	m_downloadArea = new QVBoxLayout();
	
	connect(m_hideBtn, SIGNAL(clicked()), this, SLOT(hide()));
	
	QVBoxLayout *right = new QVBoxLayout();
	right->addWidget(m_hideBtn);
	
	QHBoxLayout *bottom = new QHBoxLayout();
	bottom->addLayout(m_downloadArea);
	bottom->addLayout(right);

	QVBoxLayout *layout = new QVBoxLayout();
	layout->addWidget(m_title);
	layout->addLayout(bottom);

	this->setLayout(layout);

}

void DownloadManager::downloadRequested(const QUrl &url){
	QString path = url.path();
	QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), QFileInfo(path).fileName());
	cout<<"filename="<<qPrintable(fileName)<<endl;
	m_downloads.push_back(new Download(url, fileName));
	m_downloadArea->addWidget(new DownloadInfo(m_downloads[m_downloads.size() - 1]));
	this->show();
}

void DownloadManager::paintEvent(QPaintEvent *event){
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing, true);
	painter.setWindow(-50, -50, 100, 100);
	\
	QWidget::paintEvent(event);
}




