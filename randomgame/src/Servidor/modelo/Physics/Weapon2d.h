#ifndef WEAPON2D_H_
#define WEAPON2D_H_
#include "Bodies\Circle.h"

#define BULLET_RADIUS 0.4f

class Weapon2d : public Body{


	public:
		Weapon2d(ElementType type, float posX, float posY, float angle_x, float angle_y, float fuerzaDisparo, b2World *myWorld, GameElement *modelElement);
		void animate();
		virtual ~Weapon2d();

};


#endif