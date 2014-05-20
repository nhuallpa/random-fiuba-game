#include "Worm2d.h"


Worm2d::Worm2d(ElementType type, float posX, float posY, float h, 
	float w, float masa, float angle, b2World *myWorld, GameElement *modelElement, bool fixed) : Cuadrado(type, posX, posY, h, w, masa,angle, myWorld, modelElement, fixed)
{

	aWormActions = new WormActions(this);
	//this->ox = static_cast<GameElement*>(this->body->GetUserData())->getPosition().first;
	//this->oy = static_cast<GameElement*>(this->body->GetUserData())->getPosition().second;
	this->ox = this->body->GetPosition().x;
	this->oy = this->body->GetPosition().y;
	
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


	if ( this->ox != f.x || this->oy != f.y)
	{

		//printf("\n WormID: %d, distinto X %f to %f, Y %f to %f",myWorm->getId(), this->ox,f.x,f.y,this->oy);

		//Matar cuando pasa el agua TODO

		//Mata el worm (desactiva el cuerpo de Box2D)
		if (f.x < -15 || f.y < -15){
			this->body->SetActive(false);
			myWorm->changed = false;
			this->ox = f.x;
			this->oy = f.y;
			static_cast<Worm*>(myWorm)->setAlive(false);
			
		}else{

			//Actualiza la posicion en el modelo
			myWorm->setPosition(std::make_pair( f.x,f.y) );
			myWorm->changed = true;
			this->ox = f.x;
			this->oy = f.y;
		}
	}
	else{
		myWorm->changed = false;
	}

}


Worm2d::~Worm2d()
{
	delete aWormActions;
}



void Worm2d::animate(bool update){

	////Use userdata to reflect changes in physics to model
	//GameElement* myWorm = static_cast<GameElement*>(this->body->GetUserData());

	////si el Worm esta saltando, saltar
	//if(static_cast<Worm*>(myWorm)->isJumping())
	//{
	//	this->jump();
	//} 

	////si el Worm se esta moviendo a la izquierda, moverlo a izquierda
	//if(static_cast<Worm*>(myWorm)->isMovingLeft())
	//{
	//	this->moveLeft();
	//}

	////si el Worm se esta moviendo a la derecha, moverlo a derecha
	//if(static_cast<Worm*>(myWorm)->isMovingRight())
	//{
	//	this->moveRight();

	//}

	//b2Vec2 f = this->body->GetPosition();

	//if ( this->ox != f.x || this->oy != f.y){
	//	printf("distinto X %f to %f, Y %f to %f",this->ox,this->oy,f.x,f.y);
	//	//this->ox = f.x;
	//	//this->oy = f.y;

	//	//TODO lo desactivo al pasar el agua


	//	//Mata el worm (desactiva el cuerpo de Box2D)
	//	if (f.x < -15 || f.y < -15){
	//		this->body->SetActive(false);
	//		if ( update){
	//			myWorm->changed = false;
	//			myWorm->setPosition(std::make_pair( f.x,f.y) );
	//		}
	//		static_cast<Worm*>(myWorm)->setAlive(false);
	//		//TODO: Chequear si aca lo puedo eliminar de box2d

	//	}else{

	//		//Actualiza la posicion en el modelo
	//		
	//		if ( update){
	//			myWorm->setPosition(std::make_pair( f.x,f.y) );
	//			myWorm->changed = true;
	//			this->ox = f.x;
	//			this->oy = f.y;
	//		}
	//	}
	//}
	//else{
	//	if ( update)
	//		myWorm->changed = false;
	//}

}