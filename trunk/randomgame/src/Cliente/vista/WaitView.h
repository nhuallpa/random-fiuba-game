#pragma once

#ifndef __WAIT_VIEW_H__
#define __WAIT_VIEW_H__
#include "TextureManager.h"
#include "TextView.h"
#include "View.h"
class WaitView: public View
{
	std::string imageId;

	TextView  text;

public:
	WaitView(std::string imageId);
									
	void clean();
	
	void update();

	void draw(SDLScreen & screen);

	void setMessage(std::string msg);

	~WaitView(void);
};

#endif /** __WAIT_VIEW_H__ **/