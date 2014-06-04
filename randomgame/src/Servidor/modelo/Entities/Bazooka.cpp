#include "Bazooka.h"

Bazooka::Bazooka(int id, ElementType type, float posX, float posY) : Weapon(id, type, posX, posY){

	this->delayedExplosion = false;

}