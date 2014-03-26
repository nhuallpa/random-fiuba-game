#include "Body.h"




Body::Body(){
}

Body::Body(ElementType type, b2Body *body, int posX, int posY, float h, 
		float w, float masa, float angle, b2World *myWorld){

	this->center = b2Vec2( posX+w/2, posY+h/2 );
	this->angle = angle;
	this->masa = masa;
	this->type = type;
	this->myWorld = myWorld;
}

Body::~Body() {
}