#include "AirStrikeView.h"


AirStrikeView::AirStrikeView(int id)
	: ProjectileView(id)
{
}


AirStrikeView::~AirStrikeView(void)
{
}


void AirStrikeView::clean()
{

}
	
void AirStrikeView::update() 
{
	this->currentSprite->update();

}

void AirStrikeView::draw(SDLScreen & screen)
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


void AirStrikeView::detonate()
{
	currentSprite = &this->spriteExplosion;
	this->detonated = true;
	SoundManager::Instance().pEXPLOSION1();
}
