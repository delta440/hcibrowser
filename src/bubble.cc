#include "bubble.hh"
#include "downloadsicon.hh"

#include <QFileDialog>
#include <QFileInfo>
#include <QImage>
#include <QPainter>
#include <iostream>
using namespace std;


Bubble::Bubble(QUrl url, QWidget *parent)
	: QObject(parent), m_bounds(0,0, 50,50), m_image(0), m_dirty(true)
{
	m_finised = 0;
	m_failed = 0;
	m_clicked = 0;
	m_kbps = 0;
	m_download = 0;

	QString path = url.path();
	QString fileName = QFileDialog::getSaveFileName(parent, tr("Save File"), QFileInfo(path).fileName());
	if (fileName.size() != 0){
		cout << "Filename = " << qPrintable(fileName) << endl;
		m_download = new Download(url, fileName);
		m_filename = fileName;
		connect(m_download, SIGNAL(progress(qreal,qreal)), this, SLOT(updateProgress(qreal,qreal)));
		connect(m_download, SIGNAL(finished(bool)), this, SLOT(finished(bool)));

		//output();//TC
	}
	else
		m_failed = 1;
}


Bubble::~Bubble(){
	if (m_download) {
		m_download->stop();
		delete m_download;
	}
}

/*
void Bubble::output() const{ //TC
	cout<<"filename="<<getName().toStdString()<<endl;
	cout<<"X="<<getX()<<endl;
	cout<<"Y="<<getY()<<endl;
	cout<<"Clicked="<<clicked()<<endl;
	cout<<"kbytes ="<<m_kbytes<<endl;
	cout<<"kbps="<<m_kbps<<endl;
	cout<<endl;
}
*/

void Bubble::updateProgress(qreal kbytes, qreal kbps){
	m_kbytes = kbytes;
	m_kbps = kbps;
	// We don't care about fractional changes; only mark ourselves as
	// dirty if the rounded value changes.
	if ((int)progress() != m_prevProgress)
		m_dirty = true;

	m_prevProgress = progress();

	emit changed();
	//output(); //TC
}


bool Bubble::update() {
	m_prevPos = m_bounds.topLeft();

	// Move towards our target if we aren't being dragged. The faction is
	// chosen to get a reasonable speed at 60fps.
	if (!m_clicked) {
		QPointF next = 0.8 * (m_bounds.topLeft() - m_dest);
		m_bounds.moveTo(next + m_dest);
		// If we're close enough, then just snap to the destination, and
		// don't bother repainting.
		if (next.manhattanLength() < 0.1) m_bounds.moveTo(m_dest);
		else return true;
	}

	return false;
}


void Bubble::finished(bool okay){
	if (okay) m_finised = 1;
	else m_failed = 1;
}


void Bubble::paint(QPainter *painter) {
	if (!m_image) {
		m_image = new QImage(m_bounds.width()*3, m_bounds.height(),
							 QImage::Format_ARGB32_Premultiplied);
		m_dirty = true;
	}
	// Only recompute the image if it's dirty. Otherwise just use the
	// cached version.
	if (m_dirty) {
		m_image->fill(Qt::transparent);
		QPainter p(m_image);
		p.setBackgroundMode(Qt::TransparentMode);
		p.setRenderHint(QPainter::Antialiasing);
		p.setBrush(QBrush(Qt::white));

		QStringList parts = m_filename.split("/");
		QString dName = parts.value(parts.length() - 1);
		if(clicked()) {
			QRectF m_wideBounds(QRectF(2,2,
									   m_bounds.width()*3-4,
									   m_bounds.height()-4));

			// Draw the white background, and a soft shadow of the original
			// bubble.
			p.setPen(QPen(Qt::lightGray));
			p.setBrush(QBrush(Qt::white));
			p.drawRoundedRect(m_wideBounds, 15, 15);
			p.setBrush(QBrush(Qt::transparent));
			p.drawRoundedRect(m_bounds.width()*2+2, 2,
							  m_bounds.width()-4, m_bounds.height()-4,
							  15, 15);

			// Then draw the full width bubble with the text.
			p.setPen(QPen(Qt::blue));
			p.setBrush(QBrush(Qt::transparent));
			p.drawRoundedRect(m_wideBounds, 15, 15);
			p.drawText(m_wideBounds.left() + 2, m_wideBounds.top() + 20, dName);

			QString speed;
			if (m_kbps < 1024)
				speed = QString("Speed: %1kpbs").arg(m_kbps, 0, 'f', 1);
			else
				speed = QString("Speed: %1Mbps").arg(m_kbps/1024, 0, 'f', 1);

			p.drawText(m_wideBounds.left() + 2,
					   m_wideBounds.top() + m_wideBounds.height()/2 + 10,
					   speed);
		}
		else {
			p.setPen(QPen(Qt::blue));
			p.setBrush(QBrush(Qt::white));
			p.drawRoundedRect(m_bounds.width()*2+2, 2,
							  m_bounds.width()-4, m_bounds.height()-4,
							  15, 15);
			p.drawText(QRect(m_bounds.width()*2+4, m_bounds.height()/2 - 7, m_bounds.width()-8, 15), dName);
		}

		p.translate(4 + m_bounds.width()*2, 4);
		DownloadsIcon::paintProgressWheel(&p, m_bounds.width()-8, progress());

		m_dirty = false;
	}

	//painter->setBackgroundMode(Qt::TransparentMode);
	painter->drawImage(m_bounds.x() - 2*m_bounds.width(),
					   m_bounds.y(),
					   *m_image);
}
