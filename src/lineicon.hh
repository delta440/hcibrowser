#ifndef LINEICON_HH
#define LINEICON_HH

#include <QObject>
#include <QColor>
class QPainter;


class LineIcon : public QObject {
	Q_OBJECT
public:
	LineIcon(int width, int height, int thickness, QObject *parent = 0);
	virtual ~LineIcon() { }

	virtual void paintBackground(QPainter *p);
	virtual void paintForeground(QPainter *p) = 0;

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
	void enable(bool yes) { m_enabled = yes; }
	void hover(bool yes) { m_hovering = yes; }
	void select(bool yes) { m_selected = yes; }

private:
	bool m_enabled;
	bool m_hovering;
	bool m_selected;
	int m_width;
	int m_height;
	int m_thickness;
};

#endif // LINEICON_HH
