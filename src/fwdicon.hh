#ifndef FWDICON_HH
#define FWDICON_HH

#include "lineicon.hh"


class FwdIcon : public LineIcon {
	Q_OBJECT
public:
	FwdIcon(int height, QObject *parent = 0);
	virtual void paintForeground(QPainter *p);
};

#endif // FWDICON_HH
