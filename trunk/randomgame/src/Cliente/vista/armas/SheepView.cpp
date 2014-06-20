#include "SheepView.h"


SheepView::SheepView(int id)
	: ProjectileView(id)
{
}


SheepView::~SheepView(void)
{
}


void SheepView::clean()
{

}
	
void SheepView::update() 
{
	this->currentSprite->update();

}

void SheepView::draw(SDLScreen & screen)
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
		TextureManager::Instance().drawFillRect(screen.getRenderer(),rect,255, 0, 0, 255,true);
	}
	

}


void SheepView::detonate()
{
	currentSprite = &this->spriteExplosion;
	this->detonated = true;
	SoundManager::Instance().pEXPLOSION1();
}
