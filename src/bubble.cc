#include "bubble.hh"
#include "downloadsicon.hh"

#include <QFileDialog>
#include <QFileInfo>
#include <iostream> //TC
using namespace std;//TC

Bubble::Bubble(QUrl url, QWidget *parent): QObject(parent), m_bounds(0,0, 50,50)
{
	m_finised = 0;
	m_failed = 0;
	m_clicked = 0;

	QString path = url.path();
	QFileDialog dlg(parent, tr("Save File"), QFileInfo(path).fileName());
	QString fileName = dlg.getSaveFileName(parent, tr("Save File"), QFileInfo(path).fileName());
	if (dlg.Accepted == QDialog::Accepted){
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
	m_download->stop();
	delete m_download;
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
	emit changed();
	//output(); //TC
}

void Bubble::update() {
	m_prevPos = m_bounds.topLeft();

	// Move towards our target if we aren't being dragged. The faction is
	// chosen to get a reasonable speed at 60fps.
	if (!m_clicked) {
		QPointF next = 0.8 * (m_bounds.topLeft() - m_dest);
		m_bounds.moveTo(next + m_dest);
		// If we're close enough, then just snap to the destination.
		if (next.manhattanLength() < 0.1) m_bounds.moveTo(m_dest);
	}
}


void Bubble::finished(bool okay){
	if (okay) m_finised = 1;
	else m_failed = 1;
}


void Bubble::paint(QPainter *p) {
	//temporary bubble paint
	p->save();

	p->setPen(QPen(Qt::blue));
	p->setBrush(QBrush(Qt::white));


    p->setPen(QPen(Qt::black));
    QStringList parts = m_filename.split("/");
    QString dName = parts.value(parts.length() - 1);
    if(clicked()){
        QRectF m_wideBounds(QRectF(m_bounds.right() - m_bounds.width()*3, m_bounds.top(), m_bounds.width()*3, m_bounds.height()));
        p->drawRoundedRect(m_wideBounds, 15, 15);
        p->drawText(m_wideBounds.left() + 2, m_wideBounds.top() + 20, dName);
        p->drawText(m_wideBounds.left() + 2, m_wideBounds.top() + m_wideBounds.height()/2 + 10, QString("Speed: %1kbps").arg(m_kbps) );
    }
    else{
        p->drawRoundedRect(m_bounds, 15, 15);
        p->drawText(QRect(m_bounds.left() + 2, m_bounds.top() + m_bounds.height()/2 -5,m_bounds.width(), 15), dName);
    }
    p->translate(m_bounds.topLeft());
	DownloadsIcon::paintProgressWheel(p, m_bounds.width(), progress());
	// TODO - draw the name/speed if we're being clicked???

	p->restore();
}
