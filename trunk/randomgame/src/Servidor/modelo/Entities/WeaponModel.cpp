#include "WeaponModel.h"

WeaponModel::WeaponModel(){}

WeaponModel::~WeaponModel(){}

WeaponModel::WeaponModel(int id, int weaponid, int wormid, float posX, float posY, int aim_x, int aim_y, int intensidad){
	this->id = id;
	this->type = WEAPON;
	this->position.first = posX;
	this->position.second = posY;
	this->aim_x = aim_x;
	this->aim_y = aim_y;
	this->identifier = weaponid;
	this->parentWormId = wormid;
	this->intensidad = intensidad;
}