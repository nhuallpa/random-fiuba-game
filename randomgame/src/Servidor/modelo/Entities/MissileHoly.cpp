#include "MissileHoly.h"


MissileHoly::MissileHoly(int id):Missile(id){
	this->withDelayedExplosion=true;
	this->weaponId=HOLY;
	this->explodeTime=6;
	this->exploded = false;
}
