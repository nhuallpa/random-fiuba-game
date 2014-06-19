#include "ProjectileView.h"


ProjectileView::ProjectileView(int id)
	: View(0, 0), id(id), detonated(false)
{
	currentSprite = &this->spriteBullet;
	this->widhtLife100 = 25;
	this->widhtLifeCurrent = 25;
	this->lifeInitial = 0;
	this->currentLife = 0; //segundos
	this->enableScroll();
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

	if (domainElement->getLife() < this->currentLife) {

		float lifePorcentaje = (float)(domainElement->getLife() * 100) / (float)(this->getLifeInitial());

		this->widhtLifeCurrent = (int)((lifePorcentaje * (float)this->widhtLife100) / 100.0f);
		if (this->widhtLifeCurrent > this->widhtLife100) {
			this->widhtLifeCurrent = this->widhtLife100;
		}
		if (this->widhtLifeCurrent <= 0) {
			this->widhtLifeCurrent = 1;
		}
		this->currentLife = domainElement->getLife();
	}
}
	
void ProjectileView::update() 
{
	this->currentSprite->update();

}

// solo para los sprite
bool ProjectileView::isDetonateDone()
{
	return (detonated && currentSprite->isLastFrame());
}

// solo para los sprite
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



int ProjectileView::getLifeInitial() { 
	return this->lifeInitial;
} 
void ProjectileView::setLifeInitial(int life) {
	this->lifeInitial = life;
	this->currentLife = life; //segundos
}