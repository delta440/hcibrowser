#ifndef LINEBUTTON_HH
#define LINEBUTTON_HH

#include <QAbstractButton>
#include "lineicon.hh"
class QEvent;
class QMouseEvent;
class QPaintEvent;


class LineButton : public QAbstractButton
{
	Q_OBJECT
public:
	explicit LineButton(LineIcon *icon, QWidget *parent = 0);

public slots:
	void enable(bool yes) { m_icon->enable(yes); repaint(); }

protected:
	virtual void enterEvent(QEvent *);
	virtual void leaveEvent(QEvent *);
	virtual void mousePressEvent(QMouseEvent *);
	virtual void mouseReleaseEvent(QMouseEvent *);
	virtual void paintEvent(QPaintEvent *);

	LineIcon *m_icon;
};

#endif // LINEBUTTON_HH
