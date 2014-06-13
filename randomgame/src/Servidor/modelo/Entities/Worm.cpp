#include "Worm.h"

Worm::Worm(){
}
//Worm::Worm(int id, ElementType type, float posX, float posY, float degrees, float h, float w, float mass, bool isFixed) : GameElement(id, type, posX,  posY,  degrees,  h,  w,  mass,  isFixed)
//{
//	this->stopMoving();
//}

Worm::Worm(int id, std::string playerID, ElementType type, float posX, float posY, float degrees, float h, float w, float mass, bool isFixed)
:  GameElement(id, playerID, type, posX,  posY,  degrees,  h,  w,  mass,  isFixed) {

	this->action = MOVELESS; 
	this->stopMoving();
	this->alive = true;
	this->myLastAction = MOVELESS;
	this->stopped = false;
	this->life = MAX_WORM_LIFE;
	this->weaponId = NO_WEAPON;
	this->damaged = false;
	this->drowned = false;
}





void Worm::jump()
{
	this->stopMoving();
	jumping=true;
	this->action = JUMP;
}

void Worm::jumpRight()
{
	this->stopMoving();
	jumpingRight=true;
	this->action = JUMP_RIGHT;
}

void Worm::jumpLeft()
{
	this->stopMoving();
	jumpingLeft=true;
	this->action = JUMP_LEFT;
}


void Worm::stop()
{
	this->stopMoving();
	this->action = MOVE_STOP;
	//Worm2d* aWorm2d = (Worm2d*)this->myBody;
	//aWorm2d->getBody()->SetLinearVelocity(b2Vec2(0,0));
}

void Worm::moveLeft()
{
	this->stopMoving();
	movingLeft=true;
	//Worm2d* aWorm2d = (Worm2d*)this->myBody;
	//aWorm2d->moveLeft();
	this->action = MOVE_LEFT;
}

void Worm::moveRight()
{
	this->stopMoving();
	this->movingRight=true;
	//Worm2d* aWorm2d = (Worm2d*)this->myBody;
	//aWorm2d->moveRight();
	this->action = MOVE_RIGHT;
}

void Worm::weaponedLeft()
{
	this->stopMoving();
	this->weaponLeft=true;
	this->action = WITH_WEAPON_LEFT;
}

void Worm::weaponedRight()
{
	this->stopMoving();
	this->weaponRight=true;
	this->action = WITH_WEAPON_RIGHT;
}


void Worm::stopMoving()
{

	if ( movingRight ){
		this->action = MOVELESS_RIGHT;
	}else if ( movingLeft ){
		this->action = MOVELESS_LEFT;
	}else
		this->action = MOVELESS;
	jumping=false;
	jumpingRight=false;
	jumpingLeft=false;
	movingRight=false;
	movingLeft=false;
}

bool Worm::isStopped()
{
	return this->stopped;
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
