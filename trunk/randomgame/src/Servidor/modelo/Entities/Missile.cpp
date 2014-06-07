#include "Missile.h"


Missile::Missile(int elementId){
	this->id = elementId;
	this->type = WEAPON;
	this->exploded = false;

}

Missile::Missile()
{
}

Missile::~Missile()
{

}

void Missile::setStartTime(float aStartTime)
{
	this->startTime = aStartTime;
}

bool Missile::hasDelayedExplosion()
{
	return this->withDelayedExplosion;
}

bool Missile::hasExploded()
{ 
	return this->exploded;
}

void Missile::updateExplode(float time){

	if ( (time - this->startTime) >= this->explodeTime ){
		this->exploded = true;
	}

}