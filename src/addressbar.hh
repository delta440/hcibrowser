#ifndef ADDRESSBAR_HH
#define ADDRESSBAR_HH

#include <QLineEdit>
class QPaintEvent;


class AddressBar : public QLineEdit
{
	Q_OBJECT

	int m_progress;

public:
	explicit AddressBar(QWidget *parent = 0);

public slots:

	void setProgress(int value);

protected:

	void paintEvent(QPaintEvent *);

};

#endif // ADDRESSBAR_HH
