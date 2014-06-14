#ifndef MISSILE2DHOLY_H_
#define MISSILE2DHOLY_H_
#include "Missile2d.h"

#define BULLET_RADIUS 0.4f

class MissileHoly2d : public Missile2d{


	public:
		MissileHoly2d(ElementType type, float posX, float posY, float angle_x, float angle_y, float fuerzaDisparo, b2World *myWorld, GameElement *modelElement);
		MissileHoly2d();
		virtual ~MissileHoly2d();
		virtual void animate( float time );

};


#endif