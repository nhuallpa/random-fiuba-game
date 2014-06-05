#pragma once

#ifndef WEAPONMODEL_H_
#define WEAPONMODEL_H_

#include "../GameElement.h"
#include "../Physics/Weapon2d.h"

class WeaponModel : public GameElement{

	protected:
		bool delayedExplosion;
		bool multipleChilds;
		int amountOfMissils;
		int identifier;
		int parentWormId;
		int aim_x;
		int aim_y;
		int intensidad;

	public:
		WeaponModel();
		~WeaponModel();
		WeaponModel(int id, int weaponid, int wormId, float posX, float posY, int aim_x, int aim_y, int intensidad);
		bool hasDelayedExplosion(){ return this->delayedExplosion; }
		int getAmountOfMissils(){ return this->amountOfMissils; }
		bool hasMultipleChilds(){ return this->multipleChilds; }

};

#endif