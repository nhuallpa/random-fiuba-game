#include "GameEngine.h"
#include <list>
#include "Box2D/Collision/Shapes/b2Shape.h"
#include "Box2D/Collision/b2Collision.h"

class b2Collision;


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

	//Create terrain from BMP
	ParserYaml* aParser=ParserYaml::getInstance();
	aTerrainProcessor=new TerrainProcessor(this->myWorld,(char*)aParser->getEscenarioTierra().c_str(),atof(aParser->getMetaEps().c_str()),atoi(aParser->getMetaSca().c_str()));
	this->gameLevel.setTerrain(aTerrainProcessor);

	
	//Crea cuerpos en base a elementos del nivel (la logica de posicionamiento primero en el modelo puro de objetos)
	this->animateBodies();

	this->animateContacts();

	return true;
}


void GameEngine::floodWorld(){

	Log::d("Creando nivel de agua");
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
	Log::d("Creando cuerpos");
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
					this->gameBodies.insert(std::pair<int,Body*>((*elems).second->getId(),sq) );
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
					this->gameBodies.insert(std::pair<int,Body*>((*elems).second->getId(),sq) );
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
					this->gameBodies.insert(std::pair<int,Body*>((*elems).second->getId(),sq) );
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
					this->gameBodies.insert(std::pair<int,Body*>((*elems).second->getId(),sq) );
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
					this->gameBodies.insert(std::pair<int,Body*>((*elems).second->getId(),sq) );
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
	std::map<int,Body*>::iterator iterator = this->gameBodies.begin();
	for(iterator = this->gameBodies.begin();iterator != this->gameBodies.end(); ++iterator) {
		Body* aBody = (iterator->second);
		aBody->animate();
	}


	/* Logica del agua */
	std::set<fixturePair>::iterator it = this->myContactListener.m_fixturePairs.begin();
    std::set<fixturePair>::iterator end = this->myContactListener.m_fixturePairs.end();

	while (it != end) {
		//fixtureA = Agua
		//fixtureB = Cualquier otro cuerpo
		b2Fixture* fixtureA = it->first;
		b2Fixture* fixtureB = it->second;

		float density = fixtureA->GetDensity();
		
		std::vector<b2Vec2> intersectionPoints;
		if ( intersectionWithWater(fixtureB) ) {
			/* Velocidad que toma al caer */
			b2Vec2 vel=b2Vec2(0,-2);
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

	ParserYaml* aParser = ParserYaml::getInstance();

	for (unsigned j=0; j<aParser->getCantElem(); j++){
		Log::t("Elemento: %d",j);
		this->gameLevel.updateElementPosition(	j,
												Util::string2int(aParser->getElemId(j)),
												Util::string2float(aParser->getElemX(j)),
												Util::string2float(aParser->getElemY(j)),
												Util::string2float(aParser->getElemRot(j)));
	}
	this->updateBodyPositions();

}

void GameEngine::updateBodyPositions(){

	std::map<int, GameElement*> mmap = this->gameLevel.getEntities();
	std::map<int, GameElement*>::iterator elems = mmap.begin();

	for ( ; elems != mmap.end(); elems++) {
		std::map<int,Body*>::iterator it;
		it=this->gameBodies.find(elems->second->getId());
		it->second->setPosition(elems->second->getPosition().first,
								elems->second->getPosition().second,
								elems->second->getRotation()
								);
	}

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


/* Initial contacts review, may impact on model Element but we will inform ;) */
void GameEngine::animateContacts(){
	std::map<int,int> deletedFixtures;

	for(b2Contact* contact = this->myWorld->GetContactList(); contact; contact = contact->GetNext()){
		Log::t("recorriendo contactos");
		b2Fixture* fixtureA = contact->GetFixtureA();
		b2Fixture* fixtureB = contact->GetFixtureB();
		
		
		/* No matcheo contra el agua */
		if ( fixtureA->IsSensor()  || fixtureB->IsSensor() )
			continue;

		///* Polygon that belongs to terrain could overlap so I ommit them */
		//if ( (fixtureA->GetBody()->GetType() == b2_staticBody && (static_cast<int*>(fixtureA->GetBody()->GetUserData()) == 0 ) ) &&
		//	 (fixtureB->GetBody()->GetType() == b2_staticBody && (static_cast<int*>(fixtureB->GetBody()->GetUserData()) == 0)) ){
		//		 Log::i("terrain colliding");
		//	 continue;
		//}
		/* If A is terrain and B a DYN element body*/
		if ((fixtureA->GetBody()->GetType() == b2_staticBody &&
			(static_cast<int*>(fixtureA->GetBody()->GetUserData()) == 0) ) &&
			( (fixtureB->GetBody()->GetType() == b2_dynamicBody ) && contact->GetFixtureB()->GetBody()->GetUserData() ) )	
		{
			void* modelElementB = contact->GetFixtureB()->GetBody()->GetUserData();
			//if(contact->IsTouching())
				Log::i("Solapa A (terreno) con elemento B dinamico: %d", 
				static_cast<GameElement*>(contact->GetFixtureB()->GetBody()->GetUserData())->getId() );
				if (!deletedFixtures.count(static_cast<GameElement*>(contact->GetFixtureB()->GetBody()->GetUserData())->getId()) ){
					deletedFixtures.insert(std::make_pair(static_cast<GameElement*>(contact->GetFixtureB()->GetBody()->GetUserData())->getId(),0 ));
					
					
				}
			continue;

		}

		/* If B is terrain and A a DYN element */
		if ((fixtureB->GetBody()->GetType() == b2_staticBody &&
			(static_cast<int*>(fixtureB->GetBody()->GetUserData()) == 0) ) &&
			( (fixtureA->GetBody()->GetType() == b2_dynamicBody ) && contact->GetFixtureA()->GetBody()->GetUserData() ) )
		{
			void* modelElementA = contact->GetFixtureA()->GetBody()->GetUserData();
			//if(contact->IsTouching())
				Log::i("Solapa B (terreno) con elemento A dinamico: %d",
				static_cast<GameElement*>(contact->GetFixtureB()->GetBody()->GetUserData())->getId());
				
				
				if (!deletedFixtures.count(static_cast<GameElement*>(contact->GetFixtureA()->GetBody()->GetUserData())->getId()) ){
					deletedFixtures.insert(std::make_pair(static_cast<GameElement*>(contact->GetFixtureA()->GetBody()->GetUserData())->getId(),0 ));
					
					
				}

			continue;
		}

		/* If B is terrain and A a STATIC element */
		if ((fixtureB->GetBody()->GetType() == b2_staticBody &&
			(static_cast<int*>(fixtureB->GetBody()->GetUserData()) == 0) ) &&
			( (fixtureA->GetBody()->GetType() == b2_staticBody ) && contact->GetFixtureA()->GetBody()->GetUserData() ) )
		{
			if ( static_cast<GameElement*>(contact->GetFixtureA()->GetBody()->GetUserData())->getId() > 0 ){
				void* modelElementA = contact->GetFixtureA()->GetBody()->GetUserData();
				//if(contact->IsTouching())
					Log::i("Solapa B (terreno) con elemento A estatico: %d",
					static_cast<GameElement*>(contact->GetFixtureB()->GetBody()->GetUserData())->getId());
				if (!deletedFixtures.count(static_cast<GameElement*>(contact->GetFixtureA()->GetBody()->GetUserData())->getId()) ){
					deletedFixtures.insert(std::make_pair(static_cast<GameElement*>(contact->GetFixtureA()->GetBody()->GetUserData())->getId(),0 ));
					
					
				}

				continue;
			}
		}

		/* If A is terrain and B a STATIC element */
		if ((fixtureA->GetBody()->GetType() == b2_staticBody &&
			(static_cast<int*>(fixtureA->GetBody()->GetUserData()) == 0) ) &&
			( (fixtureB->GetBody()->GetType() == b2_staticBody ) && contact->GetFixtureB()->GetBody()->GetUserData() ) )
		{
			if ( static_cast<GameElement*>(contact->GetFixtureB()->GetBody()->GetUserData())->getId() > 0 ){
				void* modelElementB = contact->GetFixtureB()->GetBody()->GetUserData();
				//if(contact->IsTouching())
					Log::i("Solapa A (terreno) con elemento B estatico: %d",
					static_cast<GameElement*>(contact->GetFixtureB()->GetBody()->GetUserData())->getId());

					if (!deletedFixtures.count(static_cast<GameElement*>(contact->GetFixtureB()->GetBody()->GetUserData())->getId()) ){
						deletedFixtures.insert(std::make_pair(static_cast<GameElement*>(contact->GetFixtureB()->GetBody()->GetUserData())->getId(),0 ));
						
					
				}

				continue;
			}
		}

		/* If both are element bodies */
		if ( ( ((fixtureA->GetBody()->GetType() == b2_dynamicBody ) || (fixtureA->GetBody()->GetType() == b2_staticBody )) &&
				contact->GetFixtureA()->GetBody()->GetUserData() ) &&
				( ((fixtureB->GetBody()->GetType() == b2_dynamicBody ) || (fixtureB->GetBody()->GetType() == b2_staticBody ))&& 
				contact->GetFixtureB()->GetBody()->GetUserData() )
			){
				void* modelElementA = contact->GetFixtureA()->GetBody()->GetUserData();
				void* modelElementB = contact->GetFixtureB()->GetBody()->GetUserData();
				//if(contact->IsTouching())
					Log::i("Solapa elemento A (%d)con elemento B (%d)",
					static_cast<GameElement*>(contact->GetFixtureA()->GetBody()->GetUserData())->getId(),
					static_cast<GameElement*>(contact->GetFixtureB()->GetBody()->GetUserData())->getId());

				if (!deletedFixtures.count(static_cast<GameElement*>(contact->GetFixtureB()->GetBody()->GetUserData())->getId()) ){
					deletedFixtures.insert(std::make_pair(static_cast<GameElement*>(contact->GetFixtureB()->GetBody()->GetUserData())->getId(),0 ));
		
				}
		}
	}

	/* Now process all static bodies since they dont contact each other */
	b2Manifold* worldManifold = new b2Manifold();
	Log::i("Cantidad de cuerpos: %d",this->myWorld->GetBodyCount());
	for (b2Body* b=this->myWorld->GetBodyList(); b; b = b->GetNext() ){

		/*Chequeo uno contra todo el resto (estaticos), si hay resto */
		b2Body* c;
		if ( (c=b->GetNext()) && !b->GetMass() ){
			b2Fixture* f1 = b->GetFixtureList();

			for ( ; c ; c = c->GetNext()){
				
				/* If c is not static skip it */
				if (c->GetMass())
					continue;
				/* If both are part of terrain skip them */
				if ((static_cast<int*>(b->GetUserData()) == 0) &&
					(static_cast<int*>(c->GetUserData()) == 0) )
						continue;

				if ( !c->GetMass()){
					b2Fixture* f2 = c->GetFixtureList();
					
					/* poly vs poly */
					if( f1->GetType() == b2Shape::e_polygon && f2->GetType() == b2Shape::e_polygon ){
						b2CollidePolygons(	worldManifold,(b2PolygonShape*)f1->GetShape(),b->GetTransform(),
											(b2PolygonShape*)f2->GetShape(),c->GetTransform() );
					}

					if (worldManifold->pointCount > 0 ){
						
						if (static_cast<int*>(b->GetUserData()) == 0)
							Log::i("Cuerpo B = terreno");

						if (static_cast<int*>(c->GetUserData()) == 0)
							Log::i("Cuerpo C = terreno");

						Log::i("Solapamiento de estaticos: %d", 
						static_cast<GameElement*>(c->GetUserData())->getId());
						deletedFixtures.insert(std::make_pair((static_cast<GameElement*>(c->GetUserData())->getId()),0 ));

						worldManifold->pointCount = 0;

					}
				}
			}
		}
	}

	
	std::map<int,int>::iterator iterator = deletedFixtures.begin();
	for ( ; iterator != deletedFixtures.end(); iterator++) {
		Log::i("Deleting: %d",iterator->first);
		this->deleteBody(iterator->first);
	}


}


void GameEngine::deleteBody(int id){

	std::map<int,Body*>::iterator iterator;
	iterator = this->gameBodies.find(id);
	this->myWorld->DestroyBody(iterator->second->body);
	this->gameBodies.erase(iterator);
	this->gameLevel.removeEntity(id);

}


