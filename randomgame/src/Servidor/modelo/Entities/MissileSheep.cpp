#include "MissileSheep.h"


MissileSheep::MissileSheep(int id):Missile(id){
	this->withDelayedExplosion=true;
	this->weaponId=SHEEP;
	this->explodeTime=10;
	this->exploded = false;
}
