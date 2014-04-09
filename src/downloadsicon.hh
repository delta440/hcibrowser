#ifndef DOWNLOADSICON_HH
#define DOWNLOADSICON_HH

#include "lineicon.hh"


class DownloadsIcon : public LineIcon {
	Q_OBJECT
public:
	DownloadsIcon(int height, QObject *parent = 0);

	// This is a special method that paints a translucent progress wheel,
	// using the transform in the QPainter. It assumes that it is drawing
	// in the rectangle (0,0)->(size-1,size-1).
	static void paintProgressWheel(QPainter *p, qreal size, int progress);

protected:
	virtual void paintForegroundImp(QPainter *p);
};

#endif // BACKICON_HH
