#include "MissileBanana.h"


MissileBanana::MissileBanana(int id):Missile(id){
	this->withDelayedExplosion=true;
	this->weaponId=BANANA;
	this->explodeTime=5;
	this->exploded = false;
}
