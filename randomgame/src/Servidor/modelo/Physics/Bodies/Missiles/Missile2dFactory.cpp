#include "Missile2dFactory.h"


Missile2dFactory* Missile2dFactory::pInstance = NULL;

Missile2dFactory* Missile2dFactory::getInstance(){

	if(pInstance == NULL){
		pInstance = new Missile2dFactory();
	}
	return pInstance;
}


Missile2dFactory::Missile2dFactory()
{

}

Missile2dFactory::~Missile2dFactory()
{

}

Missile2d* Missile2dFactory::getMissile(int weaponId,ElementType type, float posX, float posY, float angle_x, float angle_y, float fuerzaDisparo, b2World *myWorld, GameElement *modelElement)
{
	Missile2d* aNewMissile;
	printf("\nProcessing weaponId: %d",weaponId);
	switch ( weaponId ){
	
	case BAZOOKA:
		aNewMissile = new Missile2dBazooka(type, posX, posY, angle_x,  angle_y, fuerzaDisparo, myWorld, modelElement);
		break;
	case GRENADE:
		aNewMissile = new Missile2dGrenade(type, posX, posY, angle_x,  angle_y, fuerzaDisparo, myWorld, modelElement);
		break;
	default:
		aNewMissile = new Missile2dBazooka(type, posX, posY, angle_x,  angle_y, fuerzaDisparo, myWorld, modelElement);
		break;
			
	}
	return aNewMissile;
}
