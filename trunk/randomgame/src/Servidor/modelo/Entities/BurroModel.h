#pragma once

#ifndef BURROMODEL_H_
#define BURROMODEL_H_


#include "WeaponModel.h"

class BurroModel : public WeaponModel{

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
		BurroModel();
		~BurroModel();
		BurroModel(int id, int weaponid, int wormId, float posX, float posY, int aim_x, int aim_y, int intensidad, float startTime);
		bool hasDelayedExplosion(){ return this->delayedExplosion; }
		int getAmountOfMissils(){ return this->amountOfMissils; }
		bool hasMultipleChilds(){ return this->multipleChilds; }
		bool hasExploded(){ return this->exploded; }
		void updateExplode(float time);

};

#endif