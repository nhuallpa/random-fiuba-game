#ifndef CUERPO_H_
#define CUERPO_H_

//#include "../../../utils/Vec2.h"
#include "../GameElement.h"
#include <Box2D/Common/b2Math.h>

#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f

/*
­ tipo:   rect
  x:      5
  y:      90
  ancho:  2
  alto:   1
  rot:    45
  masa:   3
  estatico:   no
  */


class b2Body;
class b2Vec2;
class b2World;
class Body {
public:
	Body();
	Body(ElementType type, b2Body *body, int posX, int posY, float h, 
		float w, float masa, float angle, b2World *myWorld);

	virtual ~Body();
	virtual b2Body* getBody(){ return this->getBody(); };
	virtual void touch(Body* touchingWith, b2World* mundo){};
	virtual void animate(){};

	virtual void setPosition(float x, float y,float rot){};
	
	float width;
	float height;
	ElementType type;
	b2Body* body;
	float angle;
	float masa;
	b2Vec2 center;
	b2World* myWorld;
};

#endif 
