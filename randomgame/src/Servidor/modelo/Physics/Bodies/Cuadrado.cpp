#include <Box2D/Box2D.h>
#include <math.h>
#include "Cuadrado.h"

Cuadrado::Cuadrado(ElementType type, b2Body *body, int posX, int posY, float h, 
		float w, float masa, float angle, b2World *myWorld)
{
	this->myWorld = myWorld;
	this->center = b2Vec2( posX+w/2, posY+h/2 );
	this->angle = angle;
	this->masa = masa;
	this->type = type;


	b2BodyDef myBodyDef;
	myBodyDef.type = b2_dynamicBody; //this will be a dynamic body
	myBodyDef.position.Set(posX+w/2, posY+h/2); //set the starting position
	myBodyDef.angle = (angle * DEGTORAD); //set the starting angle

	b2Body* dynamicBody = this->myWorld->CreateBody(&myBodyDef);
	
	b2PolygonShape boxShape;

	boxShape.SetAsBox(h,w,this->center,angle * DEGTORAD);
  
	b2FixtureDef boxFixtureDef;
	boxFixtureDef.shape = &boxShape;
	boxFixtureDef.density = 1;
	dynamicBody->CreateFixture(&boxFixtureDef);


}

void Cuadrado::animate(){
	
}

void Cuadrado::touch(Body* touchingWith, b2World* mundo) {

}

Cuadrado::~Cuadrado() {
}

