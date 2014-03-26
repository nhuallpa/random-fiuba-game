#ifndef CUERPO_H_
#define CUERPO_H_

//#include "../../../utils/Vec2.h"
#include "../GameElement.h"
#include <Box2D/Common/b2Math.h>


class b2Body;
class b2Vec2;
class b2World;

class Body {
public:
	Body();
	Body(ElementType type, b2Body *cuerpo, b2Vec2 posicionInicial, b2World *myWorld);
	virtual ~Body();

	virtual b2Body* getBody(){ return body; };
	virtual void touch(Body* touchingWith, b2World* mundo){};


	virtual void animate(){};


	ElementType type;
	b2Body* body;
	b2Vec2 posicionInicial;
	b2World* myWorld;
};

#endif 
