#ifndef STOPICON_HH
#define STOPICON_HH

#include "lineicon.hh"


class StopIcon : public LineIcon {
	Q_OBJECT
public:
	StopIcon(int height, QObject *parent = 0);
protected:
	virtual void paintForegroundImp(QPainter *p);
};

#endif // STOPICON_HH
