#include "Weapon.h"

Weapon::Weapon(){}

Weapon::~Weapon(){}

Weapon::Weapon(int id, ElementType type, float posX, float posY){
	this->id = id;
	this->type = WEAPON;
	this->position.first = posX;
	this->position.second = posY;
}