#include "HolyView.h"


HolyView::HolyView(int id)
	: ProjectileView(id)
{
	SoundManager::Instance().pHOLYGRENADE();
}


HolyView::~HolyView(void)
{
}


void HolyView::clean()
{

}
	
void HolyView::update() 
{
	this->currentSprite->update();

}

void HolyView::draw(SDLScreen & screen)
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


void HolyView::detonate()
{
	currentSprite = &this->spriteExplosion;
	this->detonated = true;
	SoundManager::Instance().pEXPLOSION1();
}
