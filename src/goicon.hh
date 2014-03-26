#ifndef GOICON_HH
#define GOICON_HH

#include "lineicon.hh"


class GoIcon : public LineIcon {
	Q_OBJECT
public:
	GoIcon(int height, QObject *parent = 0);
	virtual void paintForeground(QPainter *p);
};

#endif // GOICON_HH
