#pragma once
#ifndef __WATERVIEW_H__
#define __WATERVIEW_H__
#include "TextureManager.h"
#include "View.h"
class WaterView : public View
{
private:
	std::string imageId;

public:
	
	~WaterView(void);

	WaterView(std::string imageId, int x, int y, int width, int height);
									
	void clean();
	
	void update();

	void draw(SDLScreen & screen);
};

#endif /** __WATERVIEW_H__*/

