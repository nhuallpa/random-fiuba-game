#include <Box2D/Box2D.h>
#include <math.h>
#include "Cuadrado.h"

Cuadrado::Cuadrado(ElementType type, int posX, int posY, float h, 
		float w, float masa, float angle, b2World *myWorld, GameElement *modelElement)
{
	this->myWorld = myWorld;
	this->center = b2Vec2( posX+w/2, posY+h/2 );
	this->angle = angle;
	this->masa = masa;
	this->type = type;

	b2BodyDef myBodyDef;
	myBodyDef.type = b2_dynamicBody;
	myBodyDef.position.Set(posX+w/2, posY+h/2); //starting position (at center)
	myBodyDef.angle = (angle * DEGTORAD); 


	b2Body* dynamicBody = this->myWorld->CreateBody(&myBodyDef);
	this->body = dynamicBody;
	this->body->SetUserData(modelElement);


	b2PolygonShape boxShape;
	boxShape.SetAsBox(h,w,this->center,angle * DEGTORAD);
  
	b2FixtureDef boxFixtureDef;
	boxFixtureDef.shape = &boxShape;
	boxFixtureDef.density = 1;
	dynamicBody->CreateFixture(&boxFixtureDef);

}


//At each step links current box2d with model data
void Cuadrado::animate(){
	//Use userdata to reflect changes in physics to model
	//ToDo @aliguo
	GameElement* ge = static_cast<GameElement*>(this->body->GetUserData());
	ge->setPosition(std::make_pair(0,0));
	
}

void Cuadrado::touch(Body* touchingWith, b2World* mundo) {

}

Cuadrado::~Cuadrado() {
	// Destroy from model first
	// ToDo @aliguo
}

