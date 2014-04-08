#include "bubble.hh"

#include <QFileDialog>
#include <QFileInfo>
#include <iostream> //TC
using namespace std;//TC

Bubble::Bubble(QUrl url, QObject *parent): QObject(parent){
    m_x = 0;
    m_y = 0;
    m_finised = 0;
    m_failed = 0;
    m_clicked = 0;

    QString path = url.path();
    QFileDialog dlg(0, tr("Save File"), QFileInfo(path).fileName());
    QString fileName = dlg.getSaveFileName(0, tr("Save File"), QFileInfo(path).fileName());
    if (dlg.Accepted == QDialog::Accepted){
        cout << "Filename = " << qPrintable(fileName) << endl;
        m_download = new Download(url, fileName);
        m_filename = fileName;
        connect(m_download, SIGNAL(progress(qreal,qreal)), this, SLOT(updateProgress(qreal,qreal)));
        connect(m_download, SIGNAL(finished(bool)), this, SLOT(finished(bool)));

        output();//TC
    }
    else
        m_failed = 1;
}

Bubble::~Bubble(){
    m_download->stop();
    delete m_download;
}

int Bubble::getX() const{
    return m_x;
}

int Bubble::getY() const{
    return m_y;
}

int& Bubble::getXref(){
    return m_x;
}

int& Bubble::getYref(){
    return m_y;
}

QString Bubble::getName() const{
    return m_filename;
}

bool Bubble::clicked() const{
    return m_clicked;
}

void Bubble::setClicked(bool clicked){
    m_clicked = clicked;
}

bool Bubble::failed() const{
return m_failed;
}

double Bubble::getAngle(){
    return (m_kbytes/m_download->totalKbytes()*360);
}

void Bubble::output() const{ //TC
    cout<<"filename="<<getName().toStdString()<<endl;
    cout<<"X="<<getX()<<endl;
    cout<<"Y="<<getY()<<endl;
    cout<<"Clicked="<<clicked()<<endl;
    cout<<"kbytes ="<<m_kbytes<<endl;
    cout<<"kbps="<<m_kbps<<endl;
    cout<<endl;
}

void Bubble::updateProgress(qreal kbytes, qreal kbps){
    m_kbytes = kbytes;
    m_kbps = kbps;
    emit changed();
    output(); //TC
}

void Bubble::finished(bool okay){
    if (okay) m_finised = 1;
    else m_failed = 1;
}

