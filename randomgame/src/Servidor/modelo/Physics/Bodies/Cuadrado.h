#ifndef CUADRADO_H_
#define CUADRADO_H_


#include "../Body.h"

class Cuadrado: public Body{
public:
	Cuadrado(ElementType type, float posX, float posY, float h, 
		float w, float masa, float angle, b2World *myWorld, GameElement* modelElement);
	virtual ~Cuadrado();
	std::list<std::pair<float,float>> GetVertex();
	void animate();
	void touch(Body* touchingWith, b2World* mundo);

private:
	b2Body* createBody();
};


#endif 
