#include "DynamiteView.h"


DynamiteView::DynamiteView(int id)
	: ProjectileView(id)
{
}


DynamiteView::~DynamiteView(void)
{
}


void DynamiteView::clean()
{

}
	
void DynamiteView::update() 
{
	this->currentSprite->update();

}

void DynamiteView::draw(SDLScreen & screen)
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
													0xFF01DF3A);
}


void DynamiteView::detonate()
{
	currentSprite = &this->spriteExplosion;
	this->detonated = true;
	SoundManager::Instance().pEXPLOSION1();
}
