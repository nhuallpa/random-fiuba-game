#ifndef __ONSCROLLLISTENER__
#define __ONSCROLLLISTENER__

#include "..\Entity\ScrollEvent.h"

class OnScrollListener{
	public:
		virtual ~OnScrollListener() {}
		virtual void OnScroll(ScrollEvent e) = 0;
};

#endif



