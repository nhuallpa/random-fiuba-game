#include "DonkeyView.h"


DonkeyView::DonkeyView(int id, std::string imageId)
	: ProjectileView(id), imageId(imageId)
{
	this->enableScroll();
	std::pair<int, int> dim = TextureManager::Instance().getDimension(imageId);
	this->w = dim.first;
	this->h = dim.second;
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


int DonkeyView::getXCenter()
{
	return this->getX()-(this->w/2);
}


int DonkeyView::getYCenter()
{
	return this->getY()-(this->h/2);
}



void DonkeyView::detonate()
{
	currentSprite = &this->spriteExplosion;
	this->detonated = true;
	SoundManager::Instance().pEXPLOSION3();
}
