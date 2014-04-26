#ifndef __ONZOOMLISTENER__
#define __ONZOOMLISTENER__

#include "..\Entity\ZoomEvent.h"

class OnZoomListener{
	public:
		virtual ~OnZoomListener() {}
		virtual void OnZoom(ZoomEvent e) = 0;
};

#endif

