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

	/*Sprite spriteWalk;
	Sprite spriteBazooka;
	Sprite spriteJump;
	Sprite sprite;
	Sprite spriteJump;
*/
	TextView labelUsuario;
	TextView labelNombre;

	bool gray;

	std::string player;
	unsigned long color;

	SDL_Color white;

	WeaponId weaponId;

	int currentLife;

	int widhtLife100;
	int widhtLifeCurrent;
	
public:
	WormView(int id);
	
	std::map<std::string, Sprite> sprites;
	void clean();
	
	void update(GameElement* domainElement);

	void update();

	void draw(SDLScreen & screen);

	int getId() {return this->id;}
	std::string getPlayer();

	/*void setSpriteWalk(Sprite spriteWalk) {this->spriteWalk = spriteWalk;}
	void setSpriteJump(Sprite spriteJump) {this->spriteJump = spriteJump;}
	void setSpriteBazooka(Sprite spriteBazooka) {this->spriteBazooka = spriteBazooka;}
*/
	void selectWeapon(WeaponId idWapon);
	void unselectWeapon() {this->weaponId = NO_WEAPON;}

	WeaponId getWeaponId() {return this->weaponId;}

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

	int getW() {return this->currentSprite->getWidth();}
	int getH() {return this->currentSprite->getHeight();}

	void setUserLabel(std::string text);
	void WormView::setName(std::string text);

	~WormView(void);

};

#endif /** __WORMVIEW_H__ **/