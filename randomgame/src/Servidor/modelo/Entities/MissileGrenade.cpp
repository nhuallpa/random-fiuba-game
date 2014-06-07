#include "MissileGrenade.h"


MissileGrenade::MissileGrenade(int id):Missile(id){
	this->withDelayedExplosion=false;
	this->weaponId=GRENADE;
	this->explodeTime=3;
}
