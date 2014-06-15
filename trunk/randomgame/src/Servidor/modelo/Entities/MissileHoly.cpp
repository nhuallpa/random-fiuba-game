#include "MissileHoly.h"


MissileHoly::MissileHoly(int id):Missile(id){
	printf("\ncreating holy");
	this->withDelayedExplosion=true;
	this->weaponId=HOLY;
	this->explodeTime=3;
	this->exploded = false;
}
