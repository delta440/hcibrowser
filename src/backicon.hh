#ifndef BACKICON_HH
#define BACKICON_HH

#include "lineicon.hh"


class BackIcon : public LineIcon {
	Q_OBJECT
public:
	BackIcon(int height, QObject *parent = 0);
protected:
	virtual void paintForegroundImp(QPainter *p);
};

#endif // BACKICON_HH
