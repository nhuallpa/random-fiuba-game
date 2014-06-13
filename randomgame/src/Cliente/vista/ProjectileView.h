#pragma once

#ifndef __PROJECTILE_VIEW_H__
#define __PROJECTILE_VIEW_H__
#include "TextureManager.h"
#include "View.h"
#include "TextView.h"
#include "Sprite.h"
#include "../../Servidor/modelo/GameElement.h"
#include "../sonido/SoundManager.h"

class ProjectileView: public View
{
protected:

	int id;
	
	Sprite* currentSprite;

	TextView timerText;

	Sprite spriteBullet;

	Sprite spriteExplosion;

	bool detonated;

	
public:
	ProjectileView(int id);

	int getId() {return this->id;}

	void setSpriteBullet(Sprite spriteBullet) {this->spriteBullet = spriteBullet;}
	void setSpriteExplosion(Sprite spriteExplosion) {this->spriteExplosion = spriteExplosion;}
									
	void clean();
	
	void update(GameElement* domainElement);

	void update();

	bool isDetonateDone();

	virtual void draw(SDLScreen & screen) = 0;

	int getXCenter();

	int getYCenter();

	void detonate();

	~ProjectileView(void);

};

#endif /** __PROJECTILE_VIEW_H__ **/