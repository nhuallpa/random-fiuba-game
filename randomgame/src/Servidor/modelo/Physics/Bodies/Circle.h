#ifndef CIRCLE_H_
#define CIRCLE_H_

#include "../Body.h"

class Circle: public Body{
public:
	Circle(ElementType type, float posX, float posY, float radius, float scale, float masa, b2World *myWorld, GameElement* modelElement, bool fixed);
	virtual ~Circle();
	
	void animate();
	void touch(Body* touchingWith, b2World* mundo);

private:
	b2Body* createBody();
};


#endif 
