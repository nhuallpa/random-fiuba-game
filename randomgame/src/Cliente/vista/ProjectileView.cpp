#include "ProjectileView.h"


ProjectileView::ProjectileView(int id)
	: View(0, 0), id(id)
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

}
	
void ProjectileView::update() 
{
	this->currentSprite->update();

}

void ProjectileView::draw(SDLScreen & screen)
{ 
	

}
