#ifndef REFRESHICON_HH
#define REFRESHICON_HH

#include "lineicon.hh"


class RefreshIcon : public LineIcon {
	Q_OBJECT
public:
	RefreshIcon(int height, QObject *parent = 0);
	virtual void paintForeground(QPainter *p);
};

#endif // REFRESHICON_HH
