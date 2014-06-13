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
}


void DynamiteView::detonate()
{
	currentSprite = &this->spriteExplosion;
	this->detonated = true;
	SoundManager::Instance().pEXPLOSION1();
}
