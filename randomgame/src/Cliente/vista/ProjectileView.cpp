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
	if (domainElement->action == EXPLOSION && !this->detonated) {
		this->detonate();
	}
}
	
void ProjectileView::update() 
{
	this->currentSprite->update();

}

bool ProjectileView::isDetonateDone()
{
	return (detonated && currentSprite->isLastFrame());
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
