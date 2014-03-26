#ifndef TRIANGULO_H_
#define TRIANGULO_H_


#include "../Body.h"

class Triangulo: public Body{
public:
	Triangulo(b2World* myWorld);
	virtual ~Triangulo();
	void animate();

private:
	b2Body* createBody();
};


#endif 