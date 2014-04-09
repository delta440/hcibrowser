#ifndef LINEICON_HH
#define LINEICON_HH

#include <QObject>
#include <QColor>
class QPainter;
class QImage;


class LineIcon : public QObject {
	Q_OBJECT
public:
	LineIcon(int width, int height, int thickness, QObject *parent = 0);
	virtual ~LineIcon() { }

	void paintBackground(QPainter *p);
	void paintForeground(QPainter *p);

	bool enabled() const { return m_enabled; }
	int width() const { return m_width; }
	int height() const { return m_height; }
	int thickness() const { return m_thickness; }
	QColor foregroundColor() const {
		if (!m_enabled) return Qt::gray;
		else if (!m_selected) return Qt::black;
		else return Qt::white;
	}

public slots:
	void enable(bool yes) { m_enabled = yes; setDirty(); }
	void hover(bool yes) { m_hovering = yes; setDirty(); }
	void select(bool yes) { m_selected = yes; setDirty(); }

	// In case you do something weird and need to force the icon to
	// repaint ...
	void setDirty() { m_bgdirty = m_fgdirty = true; }

protected:
	/**
	 * Subclasses need to implement this. It will only be called when the
	 * icon changes state and needs to be redrawn.
	 */
	virtual void paintForegroundImp(QPainter *p) = 0;

private:
	bool m_enabled;
	bool m_hovering;
	bool m_selected;
	int m_width;
	int m_height;
	int m_thickness;
	bool m_bgdirty;
	bool m_fgdirty;
	QImage *m_bgimage;
	QImage *m_fgimage;
};

#endif // LINEICON_HH
