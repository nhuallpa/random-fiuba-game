#ifndef CUADRADO_H_
#define CUADRADO_H_


#include "../Body.h"

class Cuadrado: public Body{
public:
	Cuadrado(b2World* myWorld);
	virtual ~Cuadrado();
	void animate();
	void touch(Body* touchingWith, b2World* mundo);

private:
	b2Body* createBody();
};


#endif 
