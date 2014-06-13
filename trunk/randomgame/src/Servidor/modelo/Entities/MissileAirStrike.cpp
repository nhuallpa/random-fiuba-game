#include "MissileAirStrike.h"


MissileAirStrike::MissileAirStrike(int id):Missile(id){
	this->withDelayedExplosion=false;
	this->weaponId=AIRATTACK;
	this->exploded = false;
}
