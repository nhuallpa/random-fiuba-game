#include "WormActions.h"
#define FUERZA_MOV 90
#define JUMP_IMPULSE 55
#define CLIMB_FACTOR 1.1
#define JUMP_TIMEOUT 14

WormActions::WormActions(Worm2d* worm2d)
{
	this->deltaMovement=1/(float)ESCALA_UL2PX; //desplazamiento
	this->jumpTimeOut = 0;
	this->aWorm2d=worm2d;

}

void WormActions::jump()
{	

	if ( static_cast<GameElement*>(this->aWorm2d->body->GetUserData())->isGrounded() && (this->jumpTimeOut < 0) )
	{
				
                float impulse = this->aWorm2d->getMass() * JUMP_IMPULSE;
                this->aWorm2d->body->ApplyLinearImpulse( b2Vec2(0,impulse), this->aWorm2d->body->GetWorldCenter() );
				//printf("\nQuiero saltar, can I? Timeout: %d", this->jumpTimeOut);
				this->jumpTimeOut = JUMP_TIMEOUT;
        }


//if( this->jumpTimeOut < 0 )
		

}

void WormActions::moveLeft()
{
	
	float nx = static_cast<GameElement*>(this->aWorm2d->body->GetUserData())->getNormalX();
	float ny = static_cast<GameElement*>(this->aWorm2d->body->GetUserData())->getNormalY();


	if ( !static_cast<Worm*>(this->aWorm2d->body->GetUserData())->isJumping() ){
		
		if ( nx > 0.02 && ny > 0.15){
			this->aWorm2d->body->ApplyForce( b2Vec2(-FUERZA_MOV*CLIMB_FACTOR*ny,FUERZA_MOV*CLIMB_FACTOR*nx), this->aWorm2d->body->GetWorldCenter() );
			return;
		}

		if (nx < -0.02 && ny > 0.15){
			this->aWorm2d->body->ApplyForce( b2Vec2(-FUERZA_MOV*CLIMB_FACTOR*ny,FUERZA_MOV*CLIMB_FACTOR*nx), this->aWorm2d->body->GetWorldCenter() );
			return;
		}
		if (nx <= 0.02 || nx >= -0.02){
			
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
			this->aWorm2d->body->ApplyForce( b2Vec2(FUERZA_MOV*CLIMB_FACTOR*ny,-FUERZA_MOV*CLIMB_FACTOR*nx), this->aWorm2d->body->GetWorldCenter() );
			return;
		}

		if (nx < -0.02 && ny > 0.15){
			this->aWorm2d->body->ApplyForce( b2Vec2(FUERZA_MOV*CLIMB_FACTOR*ny,-FUERZA_MOV*CLIMB_FACTOR*nx), this->aWorm2d->body->GetWorldCenter() );
			return;
		}

		if (nx <= 0.02 || nx >= -0.02){
			this->aWorm2d->body->ApplyForce( b2Vec2(FUERZA_MOV,0), this->aWorm2d->body->GetWorldCenter() );
			return;
		}
	}

}

WormActions::~WormActions()
{

}
