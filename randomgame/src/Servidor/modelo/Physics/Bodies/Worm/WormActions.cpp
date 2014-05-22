#include "WormActions.h"
#define FUERZA_MOV 100

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
	//this->aWorm2d->body->SetLinearVelocity(b2Vec2(0,0));
	//if(this->aWorm2d->body->GetLinearVelocity().y ==0.0)// && jumpMovement != 0)
	if ( static_cast<GameElement*>(this->aWorm2d->body->GetUserData())->isGrounded() )
	{
				
                float impulse = this->aWorm2d->getMass() * 1.3;
                this->aWorm2d->body->ApplyLinearImpulse( b2Vec2(0,impulse), this->aWorm2d->body->GetWorldCenter() );
				//printf("\nQuiero saltar, can I?");
        }


	/*if(jumpMovement == 0)
		jumpMovement=10;
*/
}

void WormActions::moveLeft()
{
	
	float nx = static_cast<GameElement*>(this->aWorm2d->body->GetUserData())->getNormalX();
	float ny = static_cast<GameElement*>(this->aWorm2d->body->GetUserData())->getNormalY();
	//printf("\nGoinf LEFT, Normal X,Y: (%f,%f)",nx,ny);
	

		// Esta en el plano sin inclinacion
		//this->aWorm2d->body->ApplyForce( b2Vec2(-65,0), this->aWorm2d->body->GetWorldCenter() );

	if ( nx > 0.02 && ny > 0.15){
		this->aWorm2d->body->ApplyForce( b2Vec2(-FUERZA_MOV*ny,FUERZA_MOV*nx), this->aWorm2d->body->GetWorldCenter() );
		return;
	}

	if (nx < -0.02 && ny > 0.15){
		this->aWorm2d->body->ApplyForce( b2Vec2(-FUERZA_MOV*ny,FUERZA_MOV*nx), this->aWorm2d->body->GetWorldCenter() );
		return;
	}
	if ((nx <= 0.02 || nx >= -0.02) && ny > 0.15){
		//printf("\nen el plano horizontal");
		this->aWorm2d->body->ApplyForce( b2Vec2(-FUERZA_MOV,0), this->aWorm2d->body->GetWorldCenter() );
		return;
	}


}

void WormActions::moveRight()
{

	float nx = static_cast<GameElement*>(this->aWorm2d->body->GetUserData())->getNormalX();
	float ny = static_cast<GameElement*>(this->aWorm2d->body->GetUserData())->getNormalY();
	//printf("\nGoinf RIGHT, Normal X,Y: (%f,%f)",nx,ny);
	
		// Esta en el plano sin inclinacion
		//this->aWorm2d->body->ApplyForce( b2Vec2(65,0), this->aWorm2d->body->GetWorldCenter() );

		if (nx > 0.02 && ny > 0.15){
			this->aWorm2d->body->ApplyForce( b2Vec2(FUERZA_MOV*ny,-FUERZA_MOV*nx), this->aWorm2d->body->GetWorldCenter() );
			return;
		}

		if (nx < -0.02 && ny > 0.15){
			this->aWorm2d->body->ApplyForce( b2Vec2(FUERZA_MOV*ny,-FUERZA_MOV*nx), this->aWorm2d->body->GetWorldCenter() );
			return;
		}

		if ((nx <= 0.02 || nx >= -0.02) && ny > 0.15){
			this->aWorm2d->body->ApplyForce( b2Vec2(FUERZA_MOV,0), this->aWorm2d->body->GetWorldCenter() );
			return;
		}

}

WormActions::~WormActions()
{

}
