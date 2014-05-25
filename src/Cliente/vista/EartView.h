#pragma once
#ifndef __EART_VIEW__
#define __EART_VIEW__
#include "View.h"
#include "TextureManager.h"
#include "FontManager.h"
class EartView :
	public View
{
	std::string imageId;

	int counter;

	SDL_Texture* mTexture;

	/*this is filled in with a pointer to the locked pixels, appropriately offset by the locked area*/
	void* mPixels;

	/*Amount of bytes betweed rows */
	int mPitch;
public:
	EartView(std::string imageId);
	~EartView(void);
	void draw(SDLScreen & screen);

	void drawExplotion(int x, int y, int radius);

	void convertToStreamTexture();

};

#endif /* __TERRAIN_VIEW__ */
