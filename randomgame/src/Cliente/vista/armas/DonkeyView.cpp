#include "DonkeyView.h"


DonkeyView::DonkeyView(int id)
	: ProjectileView(id)
{
}


DonkeyView::~DonkeyView(void)
{
}


void DonkeyView::clean()
{

}
	
void DonkeyView::update() 
{
	this->currentSprite->update();

}

void DonkeyView::draw(SDLScreen & screen)
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


void DonkeyView::detonate()
{
	currentSprite = &this->spriteExplosion;
	this->detonated = true;
	SoundManager::Instance().pEXPLOSION1();
}
