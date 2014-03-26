#ifndef STOPICON_HH
#define STOPICON_HH

#include "lineicon.hh"


class StopIcon : public LineIcon {
	Q_OBJECT
public:
	StopIcon(int height, QObject *parent = 0);
	virtual void paintForeground(QPainter *p);
};

#endif // STOPICON_HH
