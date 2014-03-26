#ifndef DOWNLOADSICON_HH
#define DOWNLOADSICON_HH

#include "lineicon.hh"


class DownloadsIcon : public LineIcon {
	Q_OBJECT
public:
	DownloadsIcon(int height, QObject *parent = 0);
	virtual void paintForeground(QPainter *p);

	// This is a special method that paints a translucent progress wheel,
	// using the transform in the QPainter. It assumes that it is drawing
	// in the rectangle (0,0)->(size-1,size-1).
	static void paintProgressWheel(QPainter *p, qreal size, int progress);
};

#endif // BACKICON_HH
