#include <Box2D/Box2D.h>
#include <math.h>
#include "Cuadrado.h"

#define ANIMATION_SPEED 0.7

Cuadrado::Cuadrado(b2World* myWorld)
{
	this->myWorld = myWorld;


}

void Cuadrado::animate(){
	
}

void Cuadrado::touch(Body* touchingWith, b2World* mundo) {

}

Cuadrado::~Cuadrado() {
}

