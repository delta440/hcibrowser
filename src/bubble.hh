#ifndef BUBBLE_HH
#define BUBBLE_HH

#include "download.hh"

#include <QString>
#include <QObject>
class Bubble : public QObject{

    Q_OBJECT

public:
    Bubble(QUrl url, QObject *parent = 0);
    virtual ~Bubble();
    int getX() const;
    int getY() const;
    int& getXref();
    int& getYref();
    QString getName() const;
    bool clicked() const;
    bool failed() const;
    void setClicked(bool clicked);
    double getAngle();
    void output() const; //TC
private:
    Download* m_download;
    bool m_clicked;
    bool m_finised;
    bool m_failed;
    int m_x;
    int m_y;
    qreal m_kbytes;
    qreal m_kbps;
    QString m_filename;

private slots:
    void updateProgress(qreal kbytes, qreal kbps);
    void finished(bool okay);

signals:
    void changed();
};

#endif // BUBBLE_HH
