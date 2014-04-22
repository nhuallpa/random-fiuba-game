#ifndef __ONCLICKLISTENER__
#define __ONCLICKLISTENER__

#include "..\Entity\ClickEvent.h"

class Contract{
	public:
		void OnClick(ClickEvent e) = 0;
};

#endif


