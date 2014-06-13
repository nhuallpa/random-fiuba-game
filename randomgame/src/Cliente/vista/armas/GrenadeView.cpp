#include "GrenadeView.h"


GrenadeView::GrenadeView(int id)
	: ProjectileView(id)
{
}


GrenadeView::~GrenadeView(void)
{
}


void GrenadeView::clean()
{

}
	
void GrenadeView::update() 
{
	this->currentSprite->update();

}

void GrenadeView::draw(SDLScreen & screen)
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


void GrenadeView::detonate()
{
	currentSprite = &this->spriteExplosion;
	this->detonated = true;
	SoundManager::Instance().pEXPLOSION1();
}
