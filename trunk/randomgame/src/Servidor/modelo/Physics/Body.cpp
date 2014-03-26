#include "Body.h"

Body::Body(){
}

Body::Body(ElementType type, b2Body *body, b2Vec2 posicionInicial, b2World *myWorld)
	: type(type)
	, body(body)
	, posicionInicial(posicionInicial)
	, myWorld(myWorld)
{
}

Body::~Body() {
}