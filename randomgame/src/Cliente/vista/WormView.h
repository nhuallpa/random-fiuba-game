#pragma once

#ifndef __WORMVIEW_H__
#define __WORMVIEW_H__
#include "TextureManager.h"
#include "View.h"
#include "TextView.h"
#include "Sprite.h"
#include "../../Servidor/modelo/GameElement.h"
#include "../controlador/Contracts/OnMovementListener.h"
#include "StateBarView.h"


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

	TextView labelUsuario;

	bool gray;

	std::string player;
	unsigned long color;

	SDL_Color white;
	SDL_Color green;
	
public:
	WormView(int id);
									
	void clean();
	
	void update(GameElement* domainElement);

	void update();

	void draw(SDLScreen & screen);

	int getId() {return this->id;}
	
	void setSpriteWalk(Sprite spriteWalk) {this->spriteWalk = spriteWalk;}
	void setSpriteJump(Sprite spriteJump) {this->spriteJump = spriteJump;}

	void OnMovement(MovementEvent e);

	bool isSelected();
	void select();
	void deselect();

	bool isGrey();
	void putGrey();
	void quitGrey();

	void setColor(unsigned long color);
	void setPlayer(std::string player);

	int getXCenter();
	int getYCenter();

	void setUserLabel(std::string text, SDL_Renderer* renderer, TTF_Font* font);

	~WormView(void);

};

#endif /** __WORMVIEW_H__ **/