#include "Missile2d.h"

Missile2d::Missile2d()
{
}

Missile2d::Missile2d(ElementType type, float posX, float posY, float angle_x, float angle_y, float fuerzaDisparo, b2World *myWorld, GameElement *modelElement){
	
	//this->myWorld = myWorld;
	//this->center = b2Vec2( posX+(BULLET_RADIUS/2), posY+(BULLET_RADIUS/2) );

	//b2BodyDef myBodyDef;
	//myBodyDef.type = b2_dynamicBody;

	//b2FixtureDef myFixtureDef;
 //  
	//b2CircleShape circleShape;
	//circleShape.m_radius = BULLET_RADIUS;
	//circleShape.m_p.Set(0,0);

	//myFixtureDef.shape = &circleShape;
 //   myFixtureDef.density = 1;
	//myFixtureDef.friction = 0.01;
	//myFixtureDef.restitution = 0;
	//myFixtureDef.userData = (void*)UD_MISSIL;

	//printf("\nCreating weapon at: %f, %f",posX,posY);

	//myBodyDef.position.Set(posX, posY);
 //   b2Body* body = this->myWorld->CreateBody(&myBodyDef);

	//body->CreateFixture(&myFixtureDef);

	//body->SetTransform( body->GetPosition(), 0.0 );
	//body->SetFixedRotation(false);

	//this->body = body;
	//this->body->SetUserData(modelElement);

	////TODO @Bauti Aplicale impulso que consideres necesario
	//printf("\nImpulsaNdo!!");
	//this->body->ApplyLinearImpulse( b2Vec2 ( angle_x * 10, angle_y * 10 ),this->body->GetWorldCenter() );
	//printf("\nImpulsado!!");
}

Missile2d::~Missile2d(){}



Explosion Missile2d::getExplosion()
{
	this->explosion.x=this->center.x;
	this->explosion.y=this->center.y;
	return this->explosion;
}