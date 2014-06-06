#pragma once

#ifndef WEAPONMODEL_H_
#define WEAPONMODEL_H_

#include "../GameElement.h"

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
		float startTime;
		float explodeTime;

	public:
		WeaponModel();
		~WeaponModel();
		WeaponModel(int id, int weaponid, int wormId, float posX, float posY, int aim_x, int aim_y, int intensidad, float startTime);
		bool hasDelayedExplosion(){ return this->delayedExplosion; }
		int getAmountOfMissils(){ return this->amountOfMissils; }
		bool hasMultipleChilds(){ return this->multipleChilds; }
		bool hasExploded(){ return this->exploded; }
		void updateExplode(float time);

};

#endif