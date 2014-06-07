
#ifndef MISSILE_H_
#define MISSILE_H_
#include "../GameElement.h"
#include <iostream>

class Missile: public GameElement{

	protected:
		int weaponId;
		float startTime;
		float explodeTime;
		bool withDelayedExplosion;

	public:
		Missile();
		~Missile();
		Missile(int elementId);
		void setStartTime(float startTime);
		bool hasDelayedExplosion();
		bool hasExploded();
		void updateExplode(float time);

};

#endif