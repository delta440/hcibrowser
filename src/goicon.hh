#ifndef GOICON_HH
#define GOICON_HH

#include "lineicon.hh"


class GoIcon : public LineIcon {
	Q_OBJECT
public:
	GoIcon(int height, QObject *parent = 0);
protected:
	virtual void paintForegroundImp(QPainter *p);
};

#endif // GOICON_HH
