#pragma once
#ifndef __EART_VIEW__
#define __EART_VIEW__
#include "View.h"
#include "TextureManager.h"
class EartView :
	public View
{
	std::string imageId;

public:
	EartView(std::string imageId);
	~EartView(void);
	void draw(SDLScreen & screen);

};

#endif /* __TERRAIN_VIEW__ */
