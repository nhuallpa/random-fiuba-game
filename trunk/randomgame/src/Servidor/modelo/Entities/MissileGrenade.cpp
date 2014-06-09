#include "MissileGrenade.h"


MissileGrenade::MissileGrenade(int id):Missile(id){
	this->withDelayedExplosion=true;
	this->weaponId=GRENADE;
	this->explodeTime=3;
	this->exploded = false;
}
