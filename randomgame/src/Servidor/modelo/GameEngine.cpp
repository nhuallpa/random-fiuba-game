#include "GameEngine.h"
#include "Physics\Bodies\Cuadrado.h"

GameEngine::GameEngine() {
	
}

GameEngine::~GameEngine() {

}

bool GameEngine::initWorld(){
	//Crea mundo en base a defaults (Gravity y otros coeficientes)
	animateWorld();

	//Carga nivel
	return this->gameLevel.createLevel(this->gameLevel);
	
	//Crea cuerpos en base a elementos del nivel (la logica de posicionamiento primero en el modelo puro de objetos)
	animateBodies();

	//Crea contactos de Box2d
	animateJoints();
}


void GameEngine::animateWorld() {
	//ToDo: hardcoded gravity
	myWorld = new b2World(b2Vec2(0,-10.0));



}


void GameEngine::animateBodies() {

	// Recorro todos los elementos del nivel y por cada uno de ellos armo el cuerpo de box2d		
	std::multimap<std::pair<float, float>, GameElement> mmap = this->gameLevel.getEntities();
	std::multimap<std::pair<float, float>, GameElement>::iterator elems = mmap.begin();

	for ( ; elems != mmap.end(); elems++) {
		switch ((*elems).second.getType()){
			// Match de tipos y creacion de elementos en base a ello.
			case SQUARE:
				Cuadrado* sq = new Cuadrado(SQUARE, (*elems).second.getPosition().first , (*elems).second.getPosition().second, 
					(*elems).second.getHeight(), (*elems).second.getWidth(), (*elems).second.getMass(),
					(*elems).second.getRotation(), this->myWorld, &((*elems).second) );
				this->gameBodies.push_back(sq);
				break;
		}


	}

}



float GameEngine::getTimeStep () {
	return timeStep;
}

bool GameEngine::step(){

	//animateJoints();

	//Simulo (1 step)
	//this->myWorld->Step( timeStep, velocityIterations, positionIterations);
	

	//Reflect model
	std::list<Body*>::const_iterator iterator;
	for(iterator = this->gameBodies.begin();iterator != this->gameBodies.end(); ++iterator) {
		Body* aBody = *iterator;
		aBody->animate();
	}


	return true;
}


// The engine will loop separately when this runs on different sockets, not now (TP1)
bool GameEngine::loop() {
	//TODO @future
	return true;
}

int GameEngine::howManyPlayers(void){
	//TODO @future - return this->gameLevel.cantidadJugadores();
	return 1;
}

GameLevel GameEngine::getLevel(){
	return this->gameLevel;
}


void GameEngine::animateJoints() {
	//recorro todos los contactos que existen en el m_mundo

	for(b2Contact* contact = myWorld->GetContactList(); contact; contact = contact->GetNext()){

		void* data1 = contact->GetFixtureA()->GetBody()->GetUserData();
		void* data2 = contact->GetFixtureB()->GetBody()->GetUserData();

		if (data1 && data2){
			Body* body1 = static_cast<Body*> (data1);
			Body* body2 = static_cast<Body*> (data2);

			if(contact->IsTouching()){
				body1->touch(body2, myWorld);
			}

		}
	}
}