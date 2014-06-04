#pragma once

#ifndef WEAPON_H_
#define WEAPON_H_

#include "../GameElement.h"
#include "../Physics/Weapon2d.h"

class Weapon : public GameElement{

	private:
		bool delayedExplosion;
		bool multipleChilds;
		int amountOfMissils;
		WeaponId identifier;

	public:
		Weapon();
		~Weapon();
		Weapon(int id, ElementType type, float posX, float posY);
		bool hasDelayedExplosion(){ return this->delayedExplosion; }
		int getAmountOfMissils(){ return this->amountOfMissils; }
		bool hasMultipleChilds(){ return this->multipleChilds; }

};

#endif