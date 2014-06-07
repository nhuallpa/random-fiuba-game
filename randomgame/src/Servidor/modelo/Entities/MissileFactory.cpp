#include "MissileFactory.h"


MissileFactory* MissileFactory::pInstance = NULL;

MissileFactory* MissileFactory::getInstance(){

	if(pInstance == NULL){
		pInstance = new MissileFactory();
	}
	return pInstance;
}


MissileFactory::MissileFactory()
{

}

MissileFactory::~MissileFactory()
{

}

Missile* MissileFactory::getMissile(int weaponId, int elementId)
{
	Missile* aNewMissile;
	switch ( weaponId ){

	case BAZOOKA:
		aNewMissile = new MissileBazooka(elementId);
		break;
	case GRENADE:
		aNewMissile = new MissileGrenade(elementId);
		break;
	default:
		aNewMissile = new MissileBazooka(elementId);
		break;
			
	}
	return aNewMissile;
}
