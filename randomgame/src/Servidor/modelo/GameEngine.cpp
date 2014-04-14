#include "GameEngine.h"
#include <list>
#include "Box2D/Collision/Shapes/b2Shape.h"

GameEngine::GameEngine() {
	
}

GameEngine::~GameEngine() {

}

bool GameEngine::initWorld(){
	//Crea mundo en base a defaults (Gravity y otros coeficientes)
	animateWorld();

	//Carga nivel
	this->gameLevel.createLevel(this->gameLevel);
	
	this->floodWorld();
	//ToDo @aliguo
	//Create terrain from BMP
	ParserYaml* aParser=ParserYaml::getInstance();
	string path = aParser->getEscenarioTierra();
	aTerrainProcessor=new TerrainProcessor(this->myWorld,(char*)path.c_str(),1.5,100);
	this->gameLevel.setTerrain(aTerrainProcessor);

	//list<list<pair<float,float>>> *pepee = aTerrainProcessor->getListOfPolygons();


	//Crea cuerpos en base a elementos del nivel (la logica de posicionamiento primero en el modelo puro de objetos)
	animateBodies();



	return true;
}


void GameEngine::floodWorld(){

	Water* myWater = new Water( this->gameLevel.getWaterLevel(),
								this->myWorld);
	this->water = myWater;

}



void GameEngine::animateWorld() {
	//ToDo: hardcoded gravity
	this->myWorld = new b2World(b2Vec2(0,-10.0));
	//this->myContactListener = new ContactListener();
	this->myContactListener = ContactListener();
	this->myWorld->SetContactListener(&this->myContactListener);

}


void GameEngine::animateBodies() {

	// Recorro todos los elementos del nivel y por cada uno de ellos armo el cuerpo de box2d		
	std::map<int, GameElement*> mmap = this->gameLevel.getEntities();
	std::map<int, GameElement*>::iterator elems = mmap.begin();
	Log::i("Creando cuerpos");
	for ( ; elems != mmap.end(); elems++) {
		
		switch ((*elems).second->getType()){
			// Match de tipos y creacion de elementos en base a ello.
			case SQUARE:
				{
					Cuadrado* sq = new Cuadrado(SQUARE, 
											(*elems).second->getPosition().first , 
											(*elems).second->getPosition().second, 
											(*elems).second->getHeight(), 
											(*elems).second->getWidth(), 
											(*elems).second->getMass(),
											(*elems).second->getRotation(), 
											this->myWorld, 
											((*elems).second),
											(*elems).second->isFixed());
					(*elems).second->setBody(sq);
					Log::t("Puntero cuadrado: %p",sq); 
					this->gameBodies.push_back(sq);
				}
				break;
			case CIRCLE:
				{
					Circle* sq = new Circle(CIRCLE, 
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
			case HEXAGON:
				{
					Hexagon* sq = new Hexagon(HEXAGON, 
							(*elems).second->getPosition().first , 
							(*elems).second->getPosition().second,
							(*elems).second->getScale(), 
							(*elems).second->getMass(),
							(*elems).second->getRotation(),
							this->myWorld, 
							(*elems).second,
							(*elems).second->isFixed());

					(*elems).second->setBody(sq);

					Log::t("Puntero hexagono: %p",sq); 
					this->gameBodies.push_back(sq);
				}
				break;
			case TRIANGLE:
				{
					Triangle* sq = new Triangle(TRIANGLE, 
							(*elems).second->getPosition().first , 
							(*elems).second->getPosition().second,
							(*elems).second->getScale(), 
							(*elems).second->getMass(),
							(*elems).second->getRotation(),
							this->myWorld, 
							(*elems).second,
							(*elems).second->isFixed());

					(*elems).second->setBody(sq);

					Log::t("Puntero TRIANGULO: %p",sq); 
					this->gameBodies.push_back(sq);
				}
				break;
			case PENTA:
				{
					Pentagon* sq = new Pentagon(PENTA, 
							(*elems).second->getPosition().first , 
							(*elems).second->getPosition().second,
							(*elems).second->getScale(), 
							(*elems).second->getMass(),
							(*elems).second->getRotation(),
							this->myWorld, 
							(*elems).second,
							(*elems).second->isFixed());

					(*elems).second->setBody(sq);

					Log::t("Puntero PENTAGONO: %p",sq); 
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
	float32 timeStep = (1.0f/10.0f);
	//Simulo (1 step) - default values Box2D
	this->myWorld->Step(timeStep,8,3);

	//Reflect model
	std::list<Body*>::const_iterator iterator;
	for(iterator = this->gameBodies.begin();iterator != this->gameBodies.end(); ++iterator) {
		Body* aBody = *iterator;
		aBody->animate();
	}


	/* Logica del agua */
	Log::d("Check on every step");
	std::set<fixturePair>::iterator it = this->myContactListener.m_fixturePairs.begin();
    std::set<fixturePair>::iterator end = this->myContactListener.m_fixturePairs.end();

	while (it != end) {

		Log::t("Checking against water");
		//fixtureA = Agua
		//fixtureB = Cualquier otro cuerpo
		b2Fixture* fixtureA = it->first;
		b2Fixture* fixtureB = it->second;

		float density = fixtureA->GetDensity();
		
		std::vector<b2Vec2> intersectionPoints;
		if ( intersectionWithWater(fixtureB) ) {
			/* Velocidad que toma al caer */
			b2Vec2 vel=b2Vec2(0,-15);
			it->second->GetBody()->SetLinearVelocity(vel);
		}
		++it;
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

	//Load from scratch from YAML, AND UPDATE POSITIONS ON MODEL AND BOX2D
	this->gameLevel.destroyEntities();
	
	//Carga nivel
	this->gameLevel.createLevel(this->gameLevel);
	
	//Crea cuerpos en base a elementos del nivel (la logica de posicionamiento primero en el modelo puro de objetos)
	animateBodies();

}

void GameEngine::animateJoints() {
	//recorro todos los contactos que existen en el m_mundo

}

bool GameEngine::findIntersectionOfFixtures(b2Fixture* fixtureA, b2Fixture* fixtureB){

	

	return false;
}

bool GameEngine::intersectionWithWater(b2Fixture* fixture){


	if(fixture->GetShape()->GetType() == b2Shape::e_polygon){
		//Log::t("Polygon");
		b2PolygonShape* poly = (b2PolygonShape*)fixture->GetShape();
		std::vector<b2Vec2> vertex;
	
		for (int i = 0; i < poly->GetVertexCount(); i++)
			vertex.push_back( fixture->GetBody()->GetWorldPoint( poly->GetVertex(i) ) );
		for (int j = 0; j < vertex.size() ; j++){
			if ( vertex[j].y <= this->gameLevel.getWaterLevel() )
				return true;
		}
	}
	if(fixture->GetShape()->GetType() == b2Shape::e_circle){
		//Log::t("Circle");
		b2CircleShape* circ = (b2CircleShape*)fixture->GetShape();
		
		if ( (fixture->GetBody()->GetWorldPoint(b2Vec2(0.0,0.0)).y - circ->m_radius) <= this->gameLevel.getWaterLevel() )
			return true;
	}


	return false;
}

void GameEngine::animateContacts(){

	//for(b2Contact* contact = this->myWorld->GetContactList(); contact; contact = contact->GetNext()){

	//	b2Fixture* fixtureA = contact->GetFixtureA();
	//	b2Fixture* fixtureB = contact->GetFixtureB();
	//	
	//	if ( fixtureA->IsSensor() && fixtureB->GetBody()->GetType() == b2_dynamicBody )
	//		m_fixturePairs.insert( std::make_pair(fixtureA, fixtureB) );
	//	else if ( fixtureB->IsSensor() && fixtureA->GetBody()->GetType() == b2_dynamicBody )
	//		m_fixturePairs.insert( std::make_pair(fixtureB, fixtureA) );

	//}




}