#include "Worm2d.h"


Worm2d::Worm2d(ElementType type, float posX, float posY, float h, 
	float w, float masa, float angle, b2World *myWorld, GameElement *modelElement, bool fixed) : Cuadrado(type, posX, posY, h, w, masa,angle, myWorld, modelElement, fixed)
{
	aWormActions = new WormActions(this);
}
void Worm2d::jump()
{
	aWormActions->jump();
}

void Worm2d::moveLeft()
{
	aWormActions->moveLeft();
}

void Worm2d::moveRight()
{
	aWormActions->moveRight();
}

//At each step links current box2d with model data
void Worm2d::animate(){

	//Use userdata to reflect changes in physics to model
	GameElement* myWorm = static_cast<GameElement*>(this->body->GetUserData());
	//memcpy(myWorm,(this->body->GetUserData()),sizeof(Worm));

	printf("\n animating worm %d",static_cast<GameElement*>(this->body->GetUserData())->getId() );

	printf("\n animating worm %d",myWorm->getId() );

	//si el Worm esta saltando, saltar
	if(static_cast<Worm*>(myWorm)->isJumping())
	{
		this->jump();
	}

	//si el Worm se esta moviendo a la izquierda, moverlo a izquierda
	if(static_cast<Worm*>(myWorm)->isMovingLeft())
	{
		this->moveLeft();
	}

	//si el Worm se esta moviendo a la derecha, moverlo a derecha
	if(static_cast<Worm*>(myWorm)->isMovingRight())
	{
		this->moveRight();
	}


	b2Vec2 f = this->body->GetPosition();
	//Log::d("Nueva posicion (Physics): %.3f, %.3f", f.x, f.y);

	ParserYaml* aParser = ParserYaml::getInstance();
	float x = f.x;
	float y = (-1*f.y)+atoi((aParser->getEscenarioAltoU()).c_str() );
	//float y = f.y;
	myWorm->setPosition(std::make_pair( x,y) );
	//Log::d("Nueva posicion (Modelo): %.3f, %.3f", x,y);
	myWorm->setVertexList(this->GetVertex());

}


Worm2d::~Worm2d()
{
	delete aWormActions;
}
