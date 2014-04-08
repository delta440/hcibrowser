#include "bubblesbrowser.hh"
#include "bubblesoverlay.hh"
#include "bubbleswebview.hh"

#include <QNetworkReply>
#include <iostream>
#include <QResizeEvent>
#include <cmath>
using namespace std;


BubblesBrowser::BubblesBrowser(QString startPage, int wsize, QWidget *parent)
    : BasicBrowser(startPage, parent), WSIZE(wsize), BSIZE(wsize/25){
    m_bubblesOverlay = new BubblesOverlay(&m_bubbles, WSIZE, centralWidget());
    connect(m_webView, SIGNAL(mouseMEvent(QMouseEvent*)), this, SLOT(mouseMEvent(QMouseEvent*)));
    connect(m_webView, SIGNAL(mousePEvent(QMouseEvent*)), this, SLOT(mousePEvent(QMouseEvent*)));
    connect(m_webView, SIGNAL(mouseREvent(QMouseEvent*)), this, SLOT(mouseREvent(QMouseEvent*)));
}


int BubblesBrowser::convxToWindow(int x){
    return ((x / static_cast<double>(width()) * WSIZE) - (WSIZE/2.0));
}
int BubblesBrowser::convyToWindow(int y){
    return ((y / static_cast<double>(height()) * WSIZE) - (WSIZE/2.0) + (53.0/(1000.0/WSIZE)));
}

bool BubblesBrowser::overlapping(Bubble* b1, Bubble* b2, int tol){
    cout<<"check overlap"<<endl;
    double TOLERANCE = tol;
    int disX, disY;
    if(b2 == NULL){
        cout<<"ifnull"<<endl;
        disX = abs(b1->getX());
        disY = abs(WSIZE/2 - b1->getY() - BSIZE/2);
    }
    else{
        disX = abs(b1->getX() - b2->getX());
        disY = abs(b1->getY() - b2->getY());
    }
    cout<<"disx"<<disX<<"disY"<<disY<<endl;
    TOLERANCE = (TOLERANCE/100) * BSIZE;
    if(disY <= TOLERANCE && disX <= TOLERANCE){
        cout<<"returning Overlapping"<<endl; //TC
        return 1;
    }
    else
        cout<<"disy"<<disY<<"disx"<<disX<<endl;//TC
        return 0;
}

void BubblesBrowser::updateBubbles(){

cout<<"made to update"<<endl;
    for(QVector<Bubble*>::size_type i = 0; i < m_bubbles.size(); ++i){
        //keep within bounds
        if(abs(m_bubbles[i]->getX()) > WSIZE/2){
            cout<<"out of bounds x"<<m_bubbles[i]->getX()<<endl;
            if(m_bubbles[i]->getX() > 0){
                m_bubbles[i]->getXref() = WSIZE/2-BSIZE/2;
                m_bubbles[i]->setClicked(0);
                updateBubbles();
            }
            else{
                m_bubbles[i]->getXref() = -(WSIZE/2 - BSIZE/2);
                m_bubbles[i]->setClicked(0);
                updateBubbles();
            }
            m_bubblesOverlay->update();
        }
        else if(abs(m_bubbles[i]->getY()) > WSIZE/2
                || m_bubbles[i]->getY() < (-WSIZE/2) +(53.0/(1000.0/WSIZE))){
            cout<<"out of bounds y"<<m_bubbles[i]->getY()<<endl;
            if(m_bubbles[i]->getY() > 0){
                m_bubbles[i]->getYref() = WSIZE/2 - BSIZE/2;
                m_bubbles[i]->setClicked(0);
                updateBubbles();
            }
            else{
                m_bubbles[i]->getYref() = -(WSIZE/2 - BSIZE/2 -(53.0/(1000.0/WSIZE)));
                m_bubbles[i]->setClicked(0);
                updateBubbles();
            }
            m_bubblesOverlay->update();
        }


        //drag
        else if(m_bubbles[i]->clicked()){
            cout<<"dragging"<<endl; //TC
            m_bubbles[i]->getXref() = m_mousex;
            m_bubbles[i]->getYref() = m_mousey;
            m_bubblesOverlay->update();
        }

        //delete
        else if(!m_bubbles[i]->clicked() && overlapping(m_bubbles[i])){
            cout<<"delete"<<endl;
            delete m_bubbles[i];
            m_bubbles.remove(i);
            m_bubblesOverlay->update();
        }

        //keep on edge
        else if(!m_bubbles[i]->clicked()){
            cout<<"koe"<<endl;//TC
            if(m_bubbles[i]->getX() > -(WSIZE/2.0) + BSIZE/1.75){
                cout<<"not at edge"<<endl;
                m_bubbles[i]->getXref() = m_bubbles[i]->getX()-(WSIZE/500);
                m_bubblesOverlay->update();
                updateBubbles();
            }
            else if(m_bubbles[i]->getX() < -(WSIZE/2.0) + BSIZE/2.3){
                cout<<"too close to edge"<<endl;
                m_bubbles[i]->getXref() = -(WSIZE/2.0) + BSIZE/1.75;
                m_bubblesOverlay->update();
                updateBubbles();
            }
        }

        //prevent overlap
        cout<<"started overlap check"<<endl; //TC
        for(QVector<Bubble*>::size_type j = 0; j < m_bubbles.size(); ++j){
            if(j != i && overlapping(m_bubbles[i], m_bubbles[j], 110)){
                if(m_bubbles[i]->getY() <= m_bubbles[j]->getY()){
                    cout<<"iuY"<<m_bubbles[i]->getY()<<"jY"<<m_bubbles[j]->getY()<<endl;
                    m_bubbles[i]->getYref() = m_bubbles[i]->getY() - BSIZE/8;
                    m_bubbles[j]->getYref() = m_bubbles[j]->getY() + BSIZE/8;
                }
                else{
                    cout<<"idY"<<m_bubbles[i]->getY()<<"jY"<<m_bubbles[j]->getY()<<endl;
                    m_bubbles[i]->getYref() = m_bubbles[i]->getY() + BSIZE/8;
                    m_bubbles[j]->getYref() = m_bubbles[j]->getY() - BSIZE/8;
                }
                m_bubblesOverlay->update();
                updateBubbles();
            }
        }
    }
}

void BubblesBrowser::resizeEvent(QResizeEvent *event){
    m_bubblesOverlay->resize(event->size());
    event->accept();
}

void BubblesBrowser::download(const QNetworkRequest &r) {
    cout << "Request to download " << qPrintable(r.url().toString()) << endl;
    stop();
    m_bubbles.push_back(new Bubble(r.url()));
    connect(m_bubbles[m_bubbles.size()-1], SIGNAL(changed()), m_bubblesOverlay, SLOT(repaint()));
    if(m_bubbles[m_bubbles.size()-1]->failed()){
        delete m_bubbles[m_bubbles.size()-1];
        m_bubbles.remove(m_bubbles.size()-1);
    }
    else
        updateBubbles();

}


void BubblesBrowser::unsupportedContent(QNetworkReply *r) {
    cout << "Request to download " << qPrintable(r->url().toString()) << endl;
    stop();
    m_bubbles.push_back(new Bubble(r->url()));
    connect(m_bubbles[m_bubbles.size()-1], SIGNAL(changed()), m_bubblesOverlay, SLOT(repaint()));
    if(m_bubbles[m_bubbles.size()-1]->failed()){
        delete m_bubbles[m_bubbles.size()-1];
        m_bubbles.remove(m_bubbles.size()-1);
    }
    else
        updateBubbles();
}

void BubblesBrowser::mouseMEvent(QMouseEvent * event){
   m_mousex=convxToWindow(event->x());
   m_mousey=convyToWindow(event->y());
   for(QVector<Bubble*>::size_type i = 0; i < m_bubbles.size(); ++i){
       if(m_bubbles[i]->clicked())
           updateBubbles();
   }
}

void BubblesBrowser::mousePEvent(QMouseEvent *event){
    const int TOLERANCE = BSIZE/2;
    if(event->button() == Qt::LeftButton){
        bool found = 0;
        for(QVector<Bubble*>::size_type i = 0; i < m_bubbles.size() && !found; ++i){
            if(abs(m_bubbles[i]->getX() - m_mousex) <= TOLERANCE && abs(m_bubbles[i]->getY() - m_mousey) <= TOLERANCE){
                event->accept();
                m_bubbles[i]->setClicked(1);
                m_bubbles[i]->output();
                updateBubbles();
            }
        }
    }
}

void BubblesBrowser::mouseREvent(QMouseEvent *event){
    if(event->button() == Qt::LeftButton){
        for(QVector<Bubble*>::size_type i = 0; i < m_bubbles.size(); ++i){
            m_bubbles[i]->setClicked(0);
            m_bubbles[i]->output();
        }
        updateBubbles();
    }
}
