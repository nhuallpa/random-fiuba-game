#include "GameEngine.h"
#include <list>

GameEngine::GameEngine() {
	
}

GameEngine::~GameEngine() {

}

bool GameEngine::initWorld(){
	//Crea mundo en base a defaults (Gravity y otros coeficientes)
	animateWorld();

	//Carga nivel
	this->gameLevel.createLevel(this->gameLevel);
	

	//ToDo @aliguo
	//Create terrain from BMP
	ParserYaml* aParser=ParserYaml::getInstance();
	string path="C:\\random-fiuba-game\\randomgame\\randomgame\\image\\test2.bmp";//aParser->getEscenarioTierra();
	char *pepe=(char*)path.c_str();
	aTerrainProcessor=new TerrainProcessor(this->myWorld,pepe,1.5,100);
	this->gameLevel.setTerrain(aTerrainProcessor);

	//list<list<pair<float,float>>> *pepee = aTerrainProcessor->getListOfPolygons();


	//Crea cuerpos en base a elementos del nivel (la logica de posicionamiento primero en el modelo puro de objetos)
	animateBodies();

	//Crea contactos de Box2d
	animateJoints();

	return true;
}


void GameEngine::animateWorld() {
	//ToDo: hardcoded gravity
	this->myWorld = new b2World(b2Vec2(0,-10.0));
	this->myContactListener = new ContactListener();
	this->myWorld->SetContactListener(this->myContactListener);

}


void GameEngine::animateBodies() {

	// Recorro todos los elementos del nivel y por cada uno de ellos armo el cuerpo de box2d		
	std::map<int, GameElement*> mmap = this->gameLevel.getEntities();
	std::map<int, GameElement*>::iterator elems = mmap.begin();
	Log::d("Creando cuerpos");
	for ( ; elems != mmap.end(); elems++) {
		Log::t("Encontre un elemento");
		switch ((*elems).second->getType()){
			// Match de tipos y creacion de elementos en base a ello.
			case SQUARE:
				{
					Cuadrado* sq = new Cuadrado(SQUARE, (*elems).second->getPosition().first , (*elems).second->getPosition().second, 
						(*elems).second->getHeight(), (*elems).second->getWidth(), (*elems).second->getMass(),
						(*elems).second->getRotation(), this->myWorld, ((*elems).second) );
					(*elems).second->setBody(sq);
					Log::t("Puntero cuadrado: %p",sq); 
					this->gameBodies.push_back(sq);
				}
				break;
			case CIRCLE:
				{
					Circle* sq = new Circle(SQUARE, 
							(*elems).second->getPosition().first , 
							(*elems).second->getPosition().second,
							(*elems).second->getRadius(), 
							(*elems).second->getScale(), 
							(*elems).second->getMass(),
							this->myWorld, 
							(*elems).second,
							(*elems).second->isFixed());

					(*elems).second->setBody(sq);

					Log::t("Puntero circulo: %p",sq); 
					this->gameBodies.push_back(sq);
				}
				break;
		}


	}

}



float GameEngine::getTimeStep () {
	return timeStep;
}

bool GameEngine::step(){

	//animateJoints();
	float32 timeStep = (1.0f/120.0f);
	//Simulo (1 step) - default values Box2D
	this->myWorld->Step(timeStep,2,2);

	//Reflect model
	std::list<Body*>::const_iterator iterator;
	for(iterator = this->gameBodies.begin();iterator != this->gameBodies.end(); ++iterator) {
		Body* aBody = *iterator;
		aBody->animate();
	}

	//Check game Level Elements - Just TSHOOT
	std::map<int, GameElement*> mmap = this->gameLevel.getEntities();
	std::map<int, GameElement*>::iterator elems = mmap.begin();
	Log::d("TSHOOT - Listando cuerpos");
	for ( ; elems != mmap.end(); elems++) {
		Log::d("Posicion Elemento en modelo: %.3f, %.3f",
			(*elems).second->getPosition().first,
			(*elems).second->getPosition().second);
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


void GameEngine::reInitWorld(){

	//Load from scratch from YAML, first delete all
	this->gameLevel.destroyEntities();
	
	//Carga nivel
	this->gameLevel.createLevel(this->gameLevel);
	
	//Crea cuerpos en base a elementos del nivel (la logica de posicionamiento primero en el modelo puro de objetos)
	animateBodies();

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