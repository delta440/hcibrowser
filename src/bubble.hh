#ifndef BUBBLE_HH
#define BUBBLE_HH

#include "download.hh"

#include <QString>
#include <QObject>
#include <QRectF>
class QImage;
class QPainter;


class Bubble : public QObject {

	Q_OBJECT

public:
	Bubble(QUrl url, QWidget *parent = 0);
	virtual ~Bubble();

	// The bounds/position of the bubble.
	QRectF bounds() const { return m_bounds; }

	// Returns the displacement in the x direction over the last two calls
	// to update(). The value is signed, so negative values are moving left.
	double xdisplacement() const { return (m_bounds.topLeft() - m_prevPos).x(); }

	// When not clicked, the bubble will try to move towards this point.
	void setDest(QPointF p) { m_dest = p; }
	// Or you can set the absolute position.
	void setPos(QPointF p) { m_bounds.moveTo(p); }

	QString name() const { return m_filename; }
	bool clicked() const { return m_clicked; }
	bool failed() const { return m_failed; }

	// Returns the progress of the download, in the range 0-100.
	qreal progress() const {
		if (!m_download->totalKbytes()) return 0;
		return m_kbytes/m_download->totalKbytes() * 100.0;
	}

	void setClicked(bool clicked) { m_clicked = clicked;}

	// Paints the bubble using the given painter. It will be translated using
	// the value given by bounds().
	void paint(QPainter *p);

	// Updates the state of the bubble. This should be called roughly
	// 60 times a second. If a repaint is needed, this will return true.
	bool update();

	//void output() const; //TC

private:
	Download* m_download;
	bool m_clicked;
	bool m_finised;
	bool m_failed;
	QRectF m_bounds;
	QPointF m_dest;
	QPointF m_prevPos;
	qreal m_kbytes;
	qreal m_kbps;
	int m_prevProgress;
	QString m_filename;
	QImage *m_image;
	bool m_dirty;

private slots:
	void updateProgress(qreal kbytes, qreal kbps);
	void finished(bool okay);

signals:
	void changed();
};

#endif // BUBBLE_HH
