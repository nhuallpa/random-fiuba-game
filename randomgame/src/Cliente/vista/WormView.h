#pragma once

#ifndef __WORMVIEW_H__
#define __WORMVIEW_H__
#include "TextureManager.h"
#include "View.h"
#include "Sprite.h"
#include "../controlador/Contracts/OnMovementListener.h"

enum WormState {
	WORM_VIEW_DOING,
	WORM_VIEW_MOTIONLESS
};

class WormView: public View, public OnMovementListener
{
	int id;
	SDL_RendererFlip direction;

	bool selected;

	WormState state;
	
	Sprite* currentSprite;

	Sprite spriteWalk;
	Sprite spriteJump;

	
public:
	WormView(int id, int x, int y);
									
	void clean();
	
	void update();

	void draw(SDLScreen & screen);

	int getId() {return this->id;}
	
	void setSpriteWalk(Sprite spriteWalk) {this->spriteWalk = spriteWalk;}
	void setSpriteJump(Sprite spriteJump) {this->spriteJump = spriteJump;}

	void OnMovement(MovementEvent e);

	bool isSelected();
	void select();
	void deselect();

	~WormView(void);

};

#endif /** __WORMVIEW_H__ **/