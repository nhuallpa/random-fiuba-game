#include "WormActions.h"
#define FUERZA_MOV 120

WormActions::WormActions(Worm2d* worm2d)
{
	this->deltaMovement=1/(float)ESCALA_UL2PX; //desplazamiento
	this->jumpMovement=10;
	this->aWorm2d=worm2d;

}

void WormActions::jump()
{	

	
	if ( static_cast<GameElement*>(this->aWorm2d->body->GetUserData())->isGrounded() )
	{
				
                float impulse = this->aWorm2d->getMass() * 35;
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


	if ( !static_cast<Worm*>(this->aWorm2d->body->GetUserData())->isJumping() ){
		
		if ( nx > 0.02 && ny > 0.15){
			this->aWorm2d->body->ApplyForce( b2Vec2(-FUERZA_MOV*ny,FUERZA_MOV*nx), this->aWorm2d->body->GetWorldCenter() );
			return;
		}

		if (nx < -0.02 && ny > 0.15){
			this->aWorm2d->body->ApplyForce( b2Vec2(-FUERZA_MOV*ny,FUERZA_MOV*nx), this->aWorm2d->body->GetWorldCenter() );
			return;
		}
		if ((nx <= 0.02 || nx >= -0.02) && ny > 0.15){
			
			this->aWorm2d->body->ApplyForce( b2Vec2(-FUERZA_MOV,0), this->aWorm2d->body->GetWorldCenter() );
			return;
		}

	}
}

void WormActions::moveRight()
{

	float nx = static_cast<GameElement*>(this->aWorm2d->body->GetUserData())->getNormalX();
	float ny = static_cast<GameElement*>(this->aWorm2d->body->GetUserData())->getNormalY();

	if ( !static_cast<Worm*>(this->aWorm2d->body->GetUserData())->isJumping() ){

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

}

WormActions::~WormActions()
{

}
