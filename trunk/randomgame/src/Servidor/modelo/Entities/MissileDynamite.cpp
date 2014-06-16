#include "MissileDynamite.h"


MissileDynamite::MissileDynamite(int id):Missile(id){
	this->withDelayedExplosion=true;
	this->weaponId=DYNAMITE;
	this->explodeTime=3;
	this->exploded = false;
}
