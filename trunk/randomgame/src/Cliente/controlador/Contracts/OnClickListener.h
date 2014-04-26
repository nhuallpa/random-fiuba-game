#ifndef __ONCLICKLISTENER__
#define __ONCLICKLISTENER__

#include "..\Entity\ClickEvent.h"

class OnClickListener{
	public:
		virtual ~OnClickListener() {}
		virtual void OnClick(ClickEvent e) = 0;
};

#endif


