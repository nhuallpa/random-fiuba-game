#include "BananaView.h"


BananaView::BananaView(int id)
	: ProjectileView(id)
{
}


BananaView::~BananaView(void)
{
}


void BananaView::clean()
{

}
	
void BananaView::update() 
{
	this->currentSprite->update();

}

void BananaView::draw(SDLScreen & screen)
{ 
	TextureManager::Instance().drawFrame(currentSprite->getImageId(), 
										this->getXCenter(), 
										this->getYCenter(), 
										currentSprite->getWidth(), 
										currentSprite->getHeight(), 
										currentSprite->getCurrentRow(), 
										currentSprite->getCurrentFrame(), 
										screen.getRenderer(),
										false, 
										SDL_FLIP_NONE);

	if (!this->detonated) {
		SDL_Rect rect;
		rect.x = this->getX()-10;
		rect.y = this->getY()-22;
		rect.w = this->widhtLifeCurrent;
		rect.h = 5;
		TextureManager::Instance().drawBox(screen.getRenderer(), 
														rect.x, 
														rect.y, 
														rect.x + rect.w,
														rect.y + rect.h, 
														COLOR_ROJO);
	}
	

}


void BananaView::detonate()
{
	currentSprite = &this->spriteExplosion;
	this->detonated = true;
	SoundManager::Instance().pEXPLOSION1();
}
