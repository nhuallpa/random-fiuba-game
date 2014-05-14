#include "WormActions.h"


WormActions::WormActions(Worm2d* worm2d)
{
	this->deltaMovement=1/(float)ESCALA_UL2PX; //desplazamiento
	this->jumpMovement=10;
	this->aWorm2d=worm2d;

}

void WormActions::jump()
{	
	//si está en el suelo = cuando la velocidad en el eje y es igual a 0
	//this->aWorm2d->setPosition(this->aWorm2d->getBody()->GetPosition().x,this->aWorm2d->getBody()->GetPosition().y - deltaMovement,this->aWorm2d->getBody()->GetAngle());
	
	if(this->aWorm2d->body->GetLinearVelocity().y ==0.0)// && jumpMovement != 0)
        {
			//jumpMovement--;
                float impulse = this->aWorm2d->getMass() * 10;
                this->aWorm2d->body->ApplyLinearImpulse( b2Vec2(0,impulse), this->aWorm2d->body->GetWorldCenter() );
        }

	/*if(jumpMovement == 0)
		jumpMovement=10;
*/
}

void WormActions::moveLeft()
{
	//aplicar fuerza hacia la izquierda
	this->aWorm2d->setPosition(this->aWorm2d->getBody()->GetPosition().x - deltaMovement,this->aWorm2d->getBody()->GetPosition().y,this->aWorm2d->getBody()->GetAngle());
}

void WormActions::moveRight()
{
	//aplicar fuerza hacia la derecha
	this->aWorm2d->setPosition(this->aWorm2d->getBody()->GetPosition().x + deltaMovement,this->aWorm2d->getBody()->GetPosition().y,this->aWorm2d->getBody()->GetAngle());

}

WormActions::~WormActions()
{

}
