#ifndef __ZOOMEVENT__
#define __ZOOMEVENT__

enum Zoom {ZOOM_MORE,
           ZOOM_LESS};

class ZoomEvent{
	public:
		ZoomEvent(void);
		~ZoomEvent(void);
		Zoom zoom;
};

#endif