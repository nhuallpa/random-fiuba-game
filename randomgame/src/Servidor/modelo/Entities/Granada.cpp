#include "Granada.h"

Granada::Granada(int id, ElementType type, float posX, float posY) : Weapon(id, type, posX, posY){

	this->delayedExplosion = true;
}