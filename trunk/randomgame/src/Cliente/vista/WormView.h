#pragma once

#ifndef __WORMVIEW_H__
#define __WORMVIEW_H__
#include "TextureManager.h"
#include "View.h"
#include "Sprite.h"
class WormView: public View
{
	int id;
	
	Sprite* currentSprite;

	Sprite spriteWalkRight;
	Sprite spriteWalkLeft;
	Sprite spriteJump;

public:
	WormView(int id, int x, int y);
									
	void clean();
	
	void update();

	void draw(SDLScreen & screen);


	void setSpriteWalkLeft(Sprite spriteWalkLeft) {this->spriteWalkLeft = spriteWalkLeft;}
	void setSpriteWalkRight(Sprite spriteWalkRight) {this->spriteWalkRight = spriteWalkRight;}
	void setSpriteJump(Sprite spriteJump) {this->spriteJump = spriteJump;}

	~WormView(void);
};

#endif /** __WORMVIEW_H__ **/