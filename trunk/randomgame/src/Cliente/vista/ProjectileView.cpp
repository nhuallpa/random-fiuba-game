#include "ProjectileView.h"


ProjectileView::ProjectileView(int id)
	: View(0, 0), id(id), detonated(false)
{
	currentSprite = &this->spriteBullet;

}


ProjectileView::~ProjectileView(void)
{
}


void ProjectileView::clean()
{

}

void ProjectileView::update(GameElement* domainElement)
{
	std::pair<float, float> pointUL = domainElement->getPosition();
	tPoint pointSDL = TextureManager::Instance().convertPointUL2PXSDL(pointUL.first, pointUL.second);
	this->setX(pointSDL.x);
	this->setY(pointSDL.y);

	// todo: quitar
	static int count = 0;
	if (count > 100 && !this->detonated)
	{
		this->detonate();
	}
	count++;
}
	
void ProjectileView::update() 
{
	this->currentSprite->update();

}

void ProjectileView::draw(SDLScreen & screen)
{ 
	bool detonateDone = (detonated && currentSprite->isLastFrame());
	if (!detonateDone) 
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
}


int ProjectileView::getXCenter()
{
	return this->getX()-(currentSprite->getWidth()/2);
}


int ProjectileView::getYCenter()
{
	return this->getY()-(currentSprite->getHeight()/2);
}

void ProjectileView::detonate()
{
	currentSprite = &this->spriteExplosion;
	this->detonated = true;
	SoundManager::Instance().pEXPLOSION1();
}
