#include "GameEngine.h"

GameEngine::GameEngine() {
	
}

GameEngine::~GameEngine() {

}

bool GameEngine::initWorld(){
	//Crea mundo en base a defaults
	animateWorld();

	//Carga nivel
	return this->gameLevel.createLevel(this->gameLevel);
	
	//Crea cuerpos en base a elementos del nivel
	animateBodies();

	//Crea contactos
	animateJoints();
}


void GameEngine::animateWorld() {
	//ToDo: hardcoded gravity
	myWorld = new b2World(b2Vec2(0,10.0));



}


void GameEngine::animateBodies() {

	// Recorro todos los elementos del nivel y por cada uno de ellos armo el cuerpo de box2d		
	//this->gameLevel.getEntities()


}



float GameEngine::getTimeStep () {
	return timeStep;
}

bool GameEngine::step(){

	//animateJoints();

	////DAR UN PASO EN LA SIMULACION:
	//myWorld->Step( timeStep, velocityIterations, positionIterations);

	////TRADUCIRLO AL MODELO:
	//std::list<Body*>::const_iterator iterator;
	//for(iterator = bodies.begin();iterator != bodies.end(); ++iterator) {
	//	Body* aBody = *iterator;
	//	aBody->animate();
	//}
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