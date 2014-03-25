#pragma once

#ifndef __SKYVIEW_H__
#define __SKYVIEW_H__
#include "TextureManager.h"
#include "View.h"
class SkyView: public View
{
	std::string imageId;

public:
	SkyView(std::string imageId, int x, int y, int width, int height);
									
	void clean();
	
	void update();

	void draw(SDLScreen & screen);

	~SkyView(void);
};

#endif /** __SKYVIEW_H__ **/