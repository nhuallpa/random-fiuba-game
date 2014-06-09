#include "Missile2dGrenade.h"

Missile2dGrenade::Missile2dGrenade()
{

}

Missile2dGrenade::Missile2dGrenade(ElementType type, float posX, float posY, float angle_x, float angle_y, float fuerzaDisparo, b2World *myWorld, GameElement *modelElement){
	
	this->myWorld = myWorld;
	this->center = b2Vec2( posX+(BULLET_RADIUS/2), posY+(BULLET_RADIUS/2) );

	/* Importantisimo! lo seteo como weapon!! */
	this->type = type;

	b2BodyDef myBodyDef;
	myBodyDef.type = b2_dynamicBody;

	b2FixtureDef myFixtureDef;
   
	b2CircleShape circleShape;
	circleShape.m_radius = BULLET_RADIUS;
	circleShape.m_p.Set(0,0);

	myFixtureDef.shape = &circleShape;
    myFixtureDef.density = 1;
	myFixtureDef.friction = 0.01;
	myFixtureDef.restitution = 0;
	myFixtureDef.userData = (void*)UD_MISSIL;
	myBodyDef.position.Set(posX, posY);
    b2Body* body = this->myWorld->CreateBody(&myBodyDef);

	body->CreateFixture(&myFixtureDef);

		printf("\nCreating weapon at: %f, %f",posX,posY);
	body->SetTransform( body->GetPosition(), 0.0 );
	body->SetFixedRotation(false);

	this->body = body;
	this->body->SetUserData(modelElement);
		
	//SETEAR EXPLOSION
	this->explosion.radio=30;
	//impulso inicial
	this->body->ApplyLinearImpulse( b2Vec2 (10, 10 ),this->body->GetWorldCenter() );

}

Missile2dGrenade::~Missile2dGrenade(){}