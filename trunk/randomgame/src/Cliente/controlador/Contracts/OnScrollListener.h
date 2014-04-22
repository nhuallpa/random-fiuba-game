#ifndef __ONSCROLLLISTENER__
#define __ONSCROLLLISTENER__

#include "..\Entity\ScrollEvent.h"

class Contract{
	public:
		void OnScroll(ScrollEvent e) = 0;
};

#endif



