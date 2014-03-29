#pragma once
#ifndef __WATERVIEW_H__
#define __WATERVIEW_H__
#include "TextureManager.h"
#include "View.h"
class WaterView : public View
{
private:

	int height;
public:
	
	~WaterView(void);

	WaterView(int height, Uint32 color);
				
	int getHeight() {return height;}
	void setHeight(int height) {this->height = height;}

	void draw(SDLScreen & screen);
};

#endif /** __WATERVIEW_H__*/

