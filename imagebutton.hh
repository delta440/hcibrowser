#ifndef IMAGEBUTTON_HH
#define IMAGEBUTTON_HH

#include <QAbstractButton>
#include <QString>
class QIcon;
class QPaintEvent;
class QMouseEvent;


class ImageButton : public QAbstractButton
{
	Q_OBJECT

	QIcon *m_normalIcon;
	QIcon *m_hoverIcon;
	QIcon *m_pressedIcon;
	int m_state;

public:
	explicit ImageButton(
			QString normalIcon,
			QString hoverIcon,
			QString pressedIcon,
			QWidget *parent = 0);

public slots:

protected:

	virtual void enterEvent(QEvent *);
	virtual void leaveEvent(QEvent *);
	virtual void mousePressEvent(QMouseEvent *);
	virtual void mouseReleaseEvent(QMouseEvent *);
	virtual void paintEvent(QPaintEvent *);

};

#endif // IMAGEBUTTON_HH
