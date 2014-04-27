#include "WormActions.h"


WormActions::WormActions(Worm2d* worm2d)
{
	this->aWorm2d=worm2d;

}

void WormActions::jump()
{	
	//si está en el suelo = cuando la velocidad en el eje y es igual a 0
	if(this->aWorm2d->body->GetLinearVelocity().y !=0)
	{
		float impulse = this->aWorm2d->getMass() * 10;
		this->aWorm2d->body->ApplyLinearImpulse( b2Vec2(0,impulse), this->aWorm2d->body->GetWorldCenter() );
	}

}

void WormActions::moveLeft()
{
	//aplicar fuerza hacia la izquierda
	float impulse = this->aWorm2d->getMass() * 10;
	this->aWorm2d->body->ApplyLinearImpulse( b2Vec2(-impulse,0), this->aWorm2d->body->GetWorldCenter() );

}

void WormActions::moveRight()
{
	//aplicar fuerza hacia la derecha
	float impulse = this->aWorm2d->getMass() * 10;
	this->aWorm2d->body->ApplyLinearImpulse( b2Vec2(impulse,0), this->aWorm2d->body->GetWorldCenter() );

}

WormActions::~WormActions()
{

}
