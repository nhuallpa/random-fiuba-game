#include "Worm.h"

Worm::Worm(){
}
//Worm::Worm(int id, ElementType type, float posX, float posY, float degrees, float h, float w, float mass, bool isFixed) : GameElement(id, type, posX,  posY,  degrees,  h,  w,  mass,  isFixed)
//{
//	this->stopMoving();
//}

Worm::Worm(int id, std::string playerID, ElementType type, float posX, float posY, float degrees, float h, float w, float mass, bool isFixed)
:  GameElement(id, playerID, type, posX,  posY,  degrees,  h,  w,  mass,  isFixed) {

	this->stopMoving();
}

int Worm::getLife()
{
	return this->life;
}

void Worm::setLife(int newLife)
{
this->life=newLife;
}

void Worm::addLife(int moreLife)
{
 this->life= this->life+moreLife;
}

void Worm::subLife(int lessLife)
{
 this->life= this->life-lessLife;
}

void Worm::jump()
{
	jumping=true;
	Worm2d* aWorm2d = (Worm2d*)this->myBody;
	aWorm2d->jump();
}

void Worm::moveLeft()
{
	movingLeft=true;
	Worm2d* aWorm2d = (Worm2d*)this->myBody;
	aWorm2d->moveLeft();
}

void Worm::moveRight()
{
	this->movingRight=true;
	Worm2d* aWorm2d = (Worm2d*)this->myBody;
	aWorm2d->moveRight();
}


void Worm::stopMoving()
{
	jumping=false;
	movingRight=false;
	movingLeft=false;
}



bool Worm::isSelected()
{
	return this->selected;
}

bool Worm::isJumping()
{
	return this->jumping;
}

bool Worm::isMovingLeft()
{
	return this->movingLeft;
}

bool Worm::isMovingRight()
{
	return this->movingRight;
}


void Worm::select()
{
	this->selected=true;
}


void Worm::deselect()
{
	this->selected=false;
}

Worm::~Worm()
{

}
