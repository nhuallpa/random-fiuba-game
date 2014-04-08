#ifndef TRIANGULO_H_
#define TRIANGULO_H_


#include "../Body.h"

class Triangle: public Body{
public:
	Triangle(ElementType type, float posX, float posY, float angle, float scale, float masa, b2World *myWorld, GameElement* modelElement, bool fixed);
	virtual ~Triangle();
	std::list<std::pair<float,float>> GetVertex();
	void animate();
	void touch(Body* touchingWith, b2World* mundo);

private:
	b2Body* createBody();
};


#endif 