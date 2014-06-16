#include "DonkeyView.h"


DonkeyView::DonkeyView(int id, std::string imageId)
	: ProjectileView(id), imageId(imageId)
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
	TextureManager::Instance().draw(imageId.c_str(), 
										this->getXCenter(), 
										this->getYCenter(), 
										screen.getRenderer(),
										SDL_FLIP_NONE);
}


void DonkeyView::detonate()
{
	currentSprite = &this->spriteExplosion;
	this->detonated = true;
	SoundManager::Instance().pEXPLOSION3();
}
