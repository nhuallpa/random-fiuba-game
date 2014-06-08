#ifndef __ONCOORDLISTENER__
#define __ONCOORDLISTENER__

#include "..\Entity\CoordEvent.h"

class OnCoordListener{
	public:
		virtual void OnCoordinate(CoordEvent e){}
};

#endif

