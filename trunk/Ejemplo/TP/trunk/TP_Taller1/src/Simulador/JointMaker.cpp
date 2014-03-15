/*
 * JointMaker.cpp
 *
 *  Created on: Oct 9, 2013
 *      Author: lucia
 */

#include "JointMaker.h"

#include <Box2D/Box2D.h>

namespace simulador {

b2GearJoint* JointMaker::crearGearJoint(b2World* mundo, b2Body* bodyA, b2Body* bodyB,
		b2Joint* jointA, b2Joint* jointb, float ratio) {
	if ((bodyA != NULL) && (bodyB != NULL) && (jointA != NULL) && (jointb != NULL)){
		b2GearJointDef gearJointDef;
		gearJointDef.bodyA = bodyA;
		gearJointDef.bodyB = bodyB;
		gearJointDef.joint1 = jointA;
		gearJointDef.joint2 = jointb;
		gearJointDef.ratio = ratio;
		//No sé si este casteo es necesario.
		b2GearJoint* engranaje = (b2GearJoint*) mundo->CreateJoint( &gearJointDef );
		return engranaje;
	}
	return NULL;
}

b2RevoluteJoint* JointMaker::crearRevoluteJoint(b2World* mundo, b2Body* soporte,
	b2Body* cuerpo, bool habilitarMotor, float velocidadMotor, float maxTorque) {
	b2RevoluteJointDef revoluteJointDef;
	revoluteJointDef.bodyA = soporte;
	revoluteJointDef.bodyB = cuerpo;
	revoluteJointDef.collideConnected = false;
	revoluteJointDef.localAnchorA.Set(0,0);
	revoluteJointDef.localAnchorB.Set(0,0);
	revoluteJointDef.enableMotor = habilitarMotor;
	revoluteJointDef.motorSpeed = velocidadMotor;
	revoluteJointDef.maxMotorTorque = maxTorque;
	//No sé si este casteo es necesario.
	b2RevoluteJoint* joint = (b2RevoluteJoint*) mundo->CreateJoint( &revoluteJointDef );
	return joint;

}

b2RevoluteJoint* JointMaker::crearRevoluteJoint(b2World* mundo, b2Body* soporte,
	b2Body* cuerpo, bool habilitarMotor, float velocidadMotor, float maxTorque,
	bool conLimites, float lowerAng, float upperAng,b2Vec2 anchorA,b2Vec2 anchorB ) {
	b2RevoluteJointDef revoluteJointDef;
	revoluteJointDef.bodyA = soporte;
	revoluteJointDef.bodyB = cuerpo;
	revoluteJointDef.collideConnected = false;
	revoluteJointDef.localAnchorA = anchorA;
	revoluteJointDef.localAnchorB = anchorB;
	revoluteJointDef.enableMotor = habilitarMotor;
	revoluteJointDef.motorSpeed = velocidadMotor;
	revoluteJointDef.maxMotorTorque = maxTorque;
	revoluteJointDef.enableLimit = true;
	revoluteJointDef.lowerAngle = lowerAng;
	revoluteJointDef.upperAngle = upperAng;
	//No sé si este casteo es necesario.
	b2RevoluteJoint* joint = (b2RevoluteJoint*) mundo->CreateJoint( &revoluteJointDef );
	return joint;

}

b2RevoluteJoint* JointMaker::crearRevoluteJoint(b2World* mundo, b2Body* soporte,
	b2Body* cuerpo, bool habilitarMotor, float velocidadMotor, float maxTorque, b2Vec2 anchor) {
	b2RevoluteJointDef revoluteJointDef;
	revoluteJointDef.bodyA = soporte;
	revoluteJointDef.bodyB = cuerpo;
	revoluteJointDef.collideConnected = false;
	revoluteJointDef.localAnchorA.Set(0,0);
	revoluteJointDef.localAnchorB.Set(anchor.x,anchor.y);
	revoluteJointDef.enableMotor = habilitarMotor;
	revoluteJointDef.motorSpeed = velocidadMotor;
	revoluteJointDef.maxMotorTorque = maxTorque;
	//No sé si este casteo es necesario.
	b2RevoluteJoint* joint = (b2RevoluteJoint*) mundo->CreateJoint( &revoluteJointDef );
	return joint;

}

b2RevoluteJoint* JointMaker::crearRevoluteJoint(b2World* mundo, b2Body* soporte,
	b2Body* cuerpo, b2Vec2 localAnchorA, b2Vec2 localAnchorB) {
		b2RevoluteJointDef revoluteJointDef;
		revoluteJointDef.bodyA = soporte;
		revoluteJointDef.bodyB = cuerpo;
		revoluteJointDef.collideConnected = false;
		revoluteJointDef.localAnchorA.Set(localAnchorA.x,localAnchorA.y);
		revoluteJointDef.localAnchorB.Set(localAnchorB.x,localAnchorB.y);
		b2RevoluteJoint* joint = (b2RevoluteJoint*) mundo->CreateJoint( &revoluteJointDef );
		return joint;

}

b2Body* JointMaker::crearEdge(b2Vec2 desde, b2Vec2 hasta, b2World* mundo) {
	b2BodyDef myBodyDef;
	b2FixtureDef myFixtureDefBorde;
	b2EdgeShape edgeShape;
	edgeShape.Set( desde, hasta );
	myFixtureDefBorde.shape = &edgeShape;
	myBodyDef.type = b2_staticBody;
	myBodyDef.position.Set(0,0);
	b2Body* staticBody = mundo->CreateBody(&myBodyDef);
	staticBody->CreateFixture(&myFixtureDefBorde);
	return staticBody;
}

b2PulleyJoint* JointMaker::crearJointPolea(b2Body* cuerpoColgante1, b2Body* cuerpoColgante2, b2Vec2 groundAnchor1,
			b2Vec2 groundAnchor2, b2Vec2 anchor1, b2Vec2 anchor2, float ratio, float longitudA, float longitudB, b2World* mundo) {
	b2PulleyJointDef pulleyDef;
	pulleyDef.bodyA = cuerpoColgante1;
	pulleyDef.bodyB = cuerpoColgante2;
	pulleyDef.localAnchorA = anchor1;
	pulleyDef.localAnchorB = anchor2;
	pulleyDef.groundAnchorA = groundAnchor1;
	pulleyDef.groundAnchorB = groundAnchor2;
	pulleyDef.lengthA = longitudA;
	pulleyDef.lengthB = longitudB;
	pulleyDef.ratio = ratio;
	b2PulleyJoint* m_joint1 = (b2PulleyJoint*)mundo->CreateJoint(&pulleyDef);
	return m_joint1;

}

} /* namespace simulador */
