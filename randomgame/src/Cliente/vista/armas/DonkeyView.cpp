#include "DonkeyView.h"


DonkeyView::DonkeyView(int id)
	: ProjectileView(id)
{
	this->enableScroll();
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
	TextureManager::Instance().draw("donkey", 
										this->getXCenter(), 
										this->getYCenter(), 
										screen.getRenderer(),
										SDL_FLIP_NONE);
}


void DonkeyView::detonate()
{
	currentSprite = &this->spriteExplosion;
	this->detonated = true;
	SoundManager::Instance().pEXPLOSION1();
}
