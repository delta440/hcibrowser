#ifndef DOWNLOADSBUTTON_HH
#define DOWNLOADSBUTTON_HH

#include <QAbstractButton>
#include "lineicon.hh"
#include "linebutton.hh"
class QEvent;
class QMouseEvent;
class QPaintEvent;


class DownloadsButton : public LineButton
{
	Q_OBJECT
public:
	explicit DownloadsButton(int height, QWidget *parent = 0);

public slots:
	// Call this to update the progress shown by the button.
	void setProgress(int progress);

protected:
	void paintEvent(QPaintEvent *e);

private:
	int m_progress;
};

#endif // LINEBUTTON_HH
