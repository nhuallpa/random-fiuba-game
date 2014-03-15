/*
 * JointMaker.h
 *
 *  Created on: Oct 9, 2013
 *      Author: lucia
 */

#ifndef JOINTMAKER_H_
#define JOINTMAKER_H_

#include "Constantes.h"

class b2Body;
class b2Joint;
class b2GearJoint;
class b2RevoluteJoint;
class b2PulleyJoint;
class b2Vec2;
class b2World;

namespace simulador {

class JointMaker {
public:
	static b2GearJoint* crearGearJoint(b2World* mundo, b2Body* bodyA, b2Body* bodyB,
			b2Joint* jointA, b2Joint* jointB, float ratio);
	//RECORDAR SIEMPRE PASAR EL SOPORTE PRIMERO PORQUE SI NO BOX2D CUANDO
	//HAGA EL GEAR JOINT NECESITA EL CUERPO ESTÁTICO COMO BODY A :(
	static b2RevoluteJoint* crearRevoluteJoint(b2World* mundo, b2Body* soporte,
				b2Body* cuerpo, bool habilitarMotor, float velocidadMotor, float maxTorque);
	static b2RevoluteJoint* crearRevoluteJoint(b2World* mundo, b2Body* soporte,
			b2Body* cuerpo, bool habilitarMotor, float velocidadMotor, float maxTorque, b2Vec2 anchor);
	static b2RevoluteJoint* crearRevoluteJoint(b2World* mundo, b2Body* soporte,
			b2Body* cuerpo, bool habilitarMotor, float velocidadMotor, float maxTorque,
				bool conLimites, float lowerAng, float upperAng, b2Vec2 anchorA,b2Vec2 anchorB);
	static b2RevoluteJoint* crearRevoluteJoint(b2World* mundo, b2Body* soporte,
				b2Body* cuerpo, b2Vec2 anchorA,b2Vec2 anchorB);
	static b2Body* crearEdge(b2Vec2 desde, b2Vec2 hasta, b2World* mundo);
	static b2PulleyJoint* crearJointPolea(b2Body* cuerpoColgante1, b2Body* cuerpoColgante2, b2Vec2 groundAnchor1,
			b2Vec2 groundAnchor2, b2Vec2 anchor1, b2Vec2 anchor2, float ratio, float longitudA, float longitudB, b2World* mundo);
};

} /* namespace simulador */
#endif /* JOINTMAKER_H_ */
