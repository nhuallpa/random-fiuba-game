#include "BurroModel.h"

BurroModel::BurroModel(){}

BurroModel::~BurroModel(){}

BurroModel::BurroModel(int id, int weaponid, int wormid, float posX, float posY, int aim_x, int aim_y, int intensidad, float startTime){
	this->id = id;
	this->type = WEAPON;
	this->position.first = posX;
	this->position.second = posY;
	this->aim_x = aim_x;
	this->aim_y = aim_y;
	this->identifier = weaponid;
	this->parentWormId = wormid;
	this->intensidad = intensidad;
	this->exploded = false;
	this->startTime = startTime;
}

void BurroModel::updateExplode(float time){

	if ( (time - this->startTime) >= this->explodeTime ){
		this->exploded = true;
	}

}