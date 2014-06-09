#include "GameEngine.h"
#include <list>
#include "Box2D/Collision/Shapes/b2Shape.h"
#include "Box2D/Collision/b2Collision.h"
#include "Exceptions\ContourException.h"
#include "..\..\utils\ParserYaml.h"


#define UPDATE_STEPS 3
#define WATER_VELOCITY -2
#define WEAPON_STARTING_ID 100

class b2Collision;


GameEngine::GameEngine() {
	this->gameLevel = new GameLevel();
	this->weaponUniquedId = WEAPON_STARTING_ID;
	this->myTimer.start();
}

int GameEngine::getWeaponUniqueId(){
	int id = this->weaponUniquedId;
	this->weaponUniquedId = this->weaponUniquedId + 1;
	return id;
}

GameEngine::~GameEngine() {

}

bool GameEngine::initWorld(){

	this->getLevel()->updateStep = 0;

	this->gameBodies = new map<int,Body*>;
	//Crea mundo en base a defaults (Gravity y otros coeficientes)
	animateWorld();

	//Carga nivel (desde el YAML)
	this->gameLevel->createLevel(this->gameLevel);
	

	this->floodWorld();

	//Create terrain from BMP
	ParserYaml* aParser=ParserYaml::getInstance();

	this->timeStep = 1.0 / TIME_STEP;//Util::string2float(aParser->getMetaTime());
	Log::i("TimeStep: %f",this->timeStep);

	//try{
		/*aTerrainProcessor=new TerrainProcessor();
		aTerrainProcessor->process(this->myWorld,(char*)aParser->getEscenarioTierra().c_str(),atof(aParser->getMetaEps().c_str()),atoi(aParser->getMetaSca().c_str()),atoi(aParser->getEscenarioAgua().c_str()));*/
	//}
	//catch(ContourExp e){
	//	Log::e("SE CARGA TERRENO POR DEFECTO, res/images/terrain1.png, TEMPANOS DE HIELO");
	//	aParser->setTerrain("res/images/terrain1.png");
	//	aParser = ParserYaml::getInstance(aParser->getFilePath().c_str());
	//	aTerrainProcessor=new TerrainProcessor(this->myWorld,(char*)aParser->getEscenarioTierra().c_str(),atof(aParser->getMetaEps().c_str()),atoi(aParser->getMetaSca().c_str()),atoi(aParser->getEscenarioAgua().c_str()));
	//}
	
	this->gameLevel->setTerrain(this->myWorld,(char*)aParser->getEscenarioTierra().c_str(),atof(aParser->getMetaEps().c_str()),atoi(aParser->getMetaSca().c_str()),atoi(aParser->getEscenarioAgua().c_str()));

	
	//Crea cuerpos en base a elementos del nivel (la logica de posicionamiento primero en el modelo puro de objetos)
	this->animateBodies();

	this->animateContacts();

	return true;
}

bool GameEngine::getExplosion( Explosion e ){
	
	if ( !this->lastExplosions.empty() ){
		e = this->lastExplosions.front();
		this->lastExplosions.pop();
		return true;
	}
	return false;
}


void GameEngine::floodWorld(){

	Log::d("Creando nivel de agua");
	Water* myWater = new Water( this->gameLevel->getWaterLevel(),
								this->myWorld);
	this->water = myWater;

}



void GameEngine::animateWorld() {
	//ToDo: hardcoded gravity
	this->myWorld = new b2World(b2Vec2(0,-10.0));
	this->myWorld->SetGravity(b2Vec2(0,-10));
	//this->myContactListener = new ContactListener();
	this->myContactListener = ContactListener();
	this->myWorld->SetContactListener(&this->myContactListener);

}


void GameEngine::animateBodies() {

	// Recorro todos los elementos del nivel y por cada uno de ellos armo el cuerpo de box2d		
	std::map<int, GameElement*> mmap = this->gameLevel->getEntities();
	std::map<int, GameElement*>::iterator elems = mmap.begin();
	Log::d("Creando %d cuerpos",mmap.size());
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
					this->gameBodies->insert(std::pair<int,Body*>((*elems).second->getId(),sq) );
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
					this->gameBodies->insert(std::pair<int,Body*>((*elems).second->getId(),sq) );
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
					this->gameBodies->insert(std::pair<int,Body*>((*elems).second->getId(),sq) );
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
					this->gameBodies->insert(std::pair<int,Body*>((*elems).second->getId(),sq) );
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
					this->gameBodies->insert(std::pair<int,Body*>((*elems).second->getId(),sq) );
				}
				break;
		}


	}

}

void GameEngine::animateWormsFromPlayer(std::string playerID){

	std::map<int, GameElement*> mmap = this->gameLevel->getEntities();
	std::map<int, GameElement*>::iterator elems = mmap.begin();
	//Log::d("Creando cuerpos del player %s",playerID.c_str() );
	printf("\nCreando cuerpos del player %s",playerID.c_str() );
	for ( ; elems != mmap.end(); elems++) {
		if ( !elems->second->getPlayerID().compare(playerID) ){
			Worm2d* gus = new Worm2d(WORM,
								elems->second->getPosition().first,
								elems->second->getPosition().second,
								MODEL_WORM_HEIGHT,
								MODEL_WORM_WIDTH,
								elems->second->getMass(),
								0,
								this->myWorld,
								((*elems).second),
								false
								);

			(*elems).second->setBody(gus);
			printf("\nPuntero Gusano: %p",gus); 
			this->gameBodies->insert(std::pair<int,Body*>((*elems).second->getId(),gus) );
		}
	}
}

bool GameEngine::registerPlayer(std::string playerID){

	PlayerAccounting retval = this->gameLevel->acceptPlayer(playerID);
	
	if (retval == NEW_PLAYER){
		//Now animate new worms into the world
		animateWormsFromPlayer(playerID);
		return true;
	}

	if ( retval == EXISTING_PLAYER){
		
		return true;
	}
	return false;
	
}





float GameEngine::getTimeStep () {
	return timeStep;
}

bool GameEngine::step(){
	


	//Simulo (1 step) - default values Box2D
	this->myWorld->Step(this->timeStep,8,3);

	//tomo el tiempo inicial


	//Reflect model - for every body (worm)
	std::map<int,Body*>::iterator iterator = this->gameBodies->begin();
	for(iterator = this->gameBodies->begin();
		 iterator != this->gameBodies->end();
		++iterator) {
			
			if ( iterator->second->type == WORM ){
				Worm2d* aBody = static_cast<Worm2d*>(iterator->second);
				aBody->animate();
			}

			if ( iterator->second->type ==	WEAPON ) {
				
				
				if ( static_cast<Missile*>(static_cast<Missile2d*>(iterator->second)->body->GetUserData())->hasExploded() ){
					// Viene explotado del ciclo anterior, lo elimino
					printf("\nAlready exploded, deleting");
					this->deleteBody( static_cast<Missile*>(static_cast<Missile2d*>(iterator->second)->body->GetUserData())->getId() );
					continue;
				}
				
				Missile2d* aBody = static_cast<Missile2d*>(iterator->second);
				//printf("\nAnimating with time");
				aBody->animate( this->myTimer.elapsed() );

				if ( static_cast<Missile*>(static_cast<Missile2d*>(iterator->second)->body->GetUserData())->hasExploded() ){
					
					printf("\nDo explosion at position %f,%f with radius %d",
						static_cast<Missile*>(static_cast<Missile2d*>(iterator->second)->body->GetUserData())->getPosition().first + 1,
						static_cast<Missile*>(static_cast<Missile2d*>(iterator->second)->body->GetUserData())->getPosition().second + 3,
						static_cast<Missile*>(static_cast<Missile2d*>(iterator->second)->body->GetUserData())->getWeaponId()
						);
					
					// Hago agujero en Box2d
					this->doExplosion( b2Vec2( 
						static_cast<Missile*>(static_cast<Missile2d*>(iterator->second)->body->GetUserData())->getPosition().first + 1,
						static_cast<Missile*>(static_cast<Missile2d*>(iterator->second)->body->GetUserData())->getPosition().second + 3),
						static_cast<Missile*>(static_cast<Missile2d*>(iterator->second)->body->GetUserData())->getWeaponId()
						);

					// Marco como inactivo para borrar en el proximo ciclo
					static_cast<Missile2d*>(iterator->second)->body->SetActive(false);
					this->myTimer.reset();
					continue;
				}



			}

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
			b2Vec2 vel=b2Vec2(0,WATER_VELOCITY);
			it->second->GetBody()->SetLinearVelocity(vel);
		}
		++it;
	}

	return false;
}


// The engine will loop separately when this runs on different sockets, not now (TP1)
bool GameEngine::loop() {
	//TODO @future
	return true;
}

int GameEngine::howManyPlayers(void){
	//TODO @future - return this->gameLevel->cantidadJugadores();
	return 1;
}

GameLevel* GameEngine::getLevel(){
	return this->gameLevel;
}


void GameEngine::reInitWorld(){

	ParserYaml* aParser = ParserYaml::getInstance();

	for (unsigned j=0; j<aParser->getCantElem(); j++){
		Log::t("Elemento: %d",j);
		this->gameLevel->updateElementPosition(	j,
												Util::string2int(aParser->getElemId(j)),
												Util::string2float(aParser->getElemX(j)),
												Util::string2float(aParser->getElemY(j)),
												Util::string2float(aParser->getElemRot(j)));
	}
	this->updateBodyPositions();

}

void GameEngine::updateBodyPositions(){

	std::map<int, GameElement*> mmap = this->gameLevel->getEntities();
	std::map<int, GameElement*>::iterator elems = mmap.begin();

	for ( ; elems != mmap.end(); elems++) {
		std::map<int,Body*>::iterator it;
		it=this->gameBodies->find(elems->second->getId());
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

	//TODO @Music: hacer ruido de que cayo en el agua


	if(fixture->GetShape()->GetType() == b2Shape::e_polygon){
		//Log::t("Polygon");
		b2PolygonShape* poly = (b2PolygonShape*)fixture->GetShape();
		std::vector<b2Vec2> vertex;
	
		for (int i = 0; i < poly->GetVertexCount(); i++)
			vertex.push_back( fixture->GetBody()->GetWorldPoint( poly->GetVertex(i) ) );
		for (int j = 0; j < vertex.size() ; j++){
			if ( vertex[j].y <= this->gameLevel->getWaterLevel() )
				return true;
		}
	}
	if(fixture->GetShape()->GetType() == b2Shape::e_circle){
		//Log::t("Circle");
		b2CircleShape* circ = (b2CircleShape*)fixture->GetShape();
		
		if ( (fixture->GetBody()->GetWorldPoint(b2Vec2(0.0,0.0)).y - circ->m_radius) <= this->gameLevel->getWaterLevel() )
			return true;
	}


	return false;
}


/* Initial contacts review, may impact on model Element but we will inform ;) */
void GameEngine::animateContacts(){
	//
	//std::map<int,int> deletedFixtures;
	//for(b2Contact* contact = this->myWorld->GetContactList(); contact; contact = contact->GetNext()){
	//	
	//	b2Fixture* fixtureA = contact->GetFixtureA();
	//	b2Fixture* fixtureB = contact->GetFixtureB();
	//	
	//	/* No matcheo contra el agua */
	//	if ( fixtureA->IsSensor()  || fixtureB->IsSensor() )
	//		continue;

	//	/* If A is terrain and B a DYN element body*/
	//	if ((fixtureA->GetBody()->GetType() == b2_staticBody &&
	//		(static_cast<int*>(fixtureA->GetBody()->GetUserData()) == (void*)UD_WATER ) ) &&
	//		( (fixtureB->GetBody()->GetType() == b2_dynamicBody ) && contact->GetFixtureB()->GetBody()->GetUserData() ) )	
	//	{
	//		void* modelElementB = contact->GetFixtureB()->GetBody()->GetUserData();
	//		//if(contact->IsTouching())
	//			Log::i("Solapa A (terreno) con elemento B dinamico: %d", 
	//			static_cast<GameElement*>(contact->GetFixtureB()->GetBody()->GetUserData())->getId() );
	//			if (!deletedFixtures.count(static_cast<GameElement*>(contact->GetFixtureB()->GetBody()->GetUserData())->getId()) ){
	//				deletedFixtures.insert(std::make_pair(static_cast<GameElement*>(contact->GetFixtureB()->GetBody()->GetUserData())->getId(),0 ));
	//				
	//			}
	//		continue;
	//	}

	//	/* If B is terrain and A a DYN element */
	//	if ((fixtureB->GetBody()->GetType() == b2_staticBody &&
	//		(static_cast<int*>(fixtureB->GetBody()->GetUserData()) == (void*)UD_WATER ) ) &&
	//		( (fixtureA->GetBody()->GetType() == b2_dynamicBody ) && contact->GetFixtureA()->GetBody()->GetUserData() ) )
	//	{
	//		void* modelElementA = contact->GetFixtureA()->GetBody()->GetUserData();
	//		//if(contact->IsTouching())
	//			Log::i("Solapa B (terreno) con elemento A dinamico: %d",
	//			static_cast<GameElement*>(contact->GetFixtureB()->GetBody()->GetUserData())->getId());
	//			
	//			
	//			if (!deletedFixtures.count(static_cast<GameElement*>(contact->GetFixtureA()->GetBody()->GetUserData())->getId()) ){
	//				deletedFixtures.insert(std::make_pair(static_cast<GameElement*>(contact->GetFixtureA()->GetBody()->GetUserData())->getId(),0 ));
	//				
	//			}
	//		continue;
	//	}

	//	/* If B is terrain and A a STATIC element */
	//	if ((fixtureB->GetBody()->GetType() == b2_staticBody &&
	//		(static_cast<int*>(fixtureB->GetBody()->GetUserData()) == (void*)UD_WATER ) ) &&
	//		( (fixtureA->GetBody()->GetType() == b2_staticBody ) && contact->GetFixtureA()->GetBody()->GetUserData() ) )
	//	{
	//		if ( static_cast<GameElement*>(contact->GetFixtureA()->GetBody()->GetUserData())->getId() > 0 ){
	//			void* modelElementA = contact->GetFixtureA()->GetBody()->GetUserData();
	//			//if(contact->IsTouching())
	//				Log::i("Solapa B (terreno) con elemento A estatico: %d",
	//				static_cast<GameElement*>(contact->GetFixtureB()->GetBody()->GetUserData())->getId());
	//			if (!deletedFixtures.count(static_cast<GameElement*>(contact->GetFixtureA()->GetBody()->GetUserData())->getId()) ){
	//				deletedFixtures.insert(std::make_pair(static_cast<GameElement*>(contact->GetFixtureA()->GetBody()->GetUserData())->getId(),0 ));
	//				
	//			}
	//			continue;
	//		}
	//	}

	//	/* If A is terrain and B a STATIC element */
	//	if ((fixtureA->GetBody()->GetType() == b2_staticBody &&
	//		(static_cast<int*>(fixtureA->GetBody()->GetUserData()) == (void*)UD_WATER ) ) &&
	//		( (fixtureB->GetBody()->GetType() == b2_staticBody ) && contact->GetFixtureB()->GetBody()->GetUserData() ) )
	//	{
	//		if ( static_cast<GameElement*>(contact->GetFixtureB()->GetBody()->GetUserData())->getId() > 0 ){
	//			void* modelElementB = contact->GetFixtureB()->GetBody()->GetUserData();
	//			//if(contact->IsTouching())
	//				Log::i("Solapa A (terreno) con elemento B estatico: %d",
	//				static_cast<GameElement*>(contact->GetFixtureB()->GetBody()->GetUserData())->getId());

	//				if (!deletedFixtures.count(static_cast<GameElement*>(contact->GetFixtureB()->GetBody()->GetUserData())->getId()) ){
	//					deletedFixtures.insert(std::make_pair(static_cast<GameElement*>(contact->GetFixtureB()->GetBody()->GetUserData())->getId(),0 ));
	//			}
	//			continue;
	//		}
	//	}

	//	/* If both are element bodies */
	//	if ( ( ((fixtureA->GetBody()->GetType() == b2_dynamicBody ) || (fixtureA->GetBody()->GetType() == b2_staticBody )) &&
	//			contact->GetFixtureA()->GetBody()->GetUserData() ) &&
	//			( ((fixtureB->GetBody()->GetType() == b2_dynamicBody ) || (fixtureB->GetBody()->GetType() == b2_staticBody ))&& 
	//			contact->GetFixtureB()->GetBody()->GetUserData() )
	//		){
	//			void* modelElementA = contact->GetFixtureA()->GetBody()->GetUserData();
	//			void* modelElementB = contact->GetFixtureB()->GetBody()->GetUserData();
	//			//if(contact->IsTouching())
	//				Log::i("Solapa elemento A (%d)con elemento B (%d)",
	//				static_cast<GameElement*>(contact->GetFixtureA()->GetBody()->GetUserData())->getId(),
	//				static_cast<GameElement*>(contact->GetFixtureB()->GetBody()->GetUserData())->getId());

	//			if (!deletedFixtures.count(static_cast<GameElement*>(contact->GetFixtureB()->GetBody()->GetUserData())->getId()) ){
	//				deletedFixtures.insert(std::make_pair(static_cast<GameElement*>(contact->GetFixtureB()->GetBody()->GetUserData())->getId(),0 ));
	//	
	//			}
	//	}
	//}

	///* Now process all static bodies since they dont contact each other */
	//Log::i("Proceso estaticos");


	//b2Manifold* worldManifold = new b2Manifold();
	//for (b2Body* b=this->myWorld->GetBodyList(); b; b = b->GetNext() ){

	//	/*Chequeo uno contra todo el resto (estaticos), si hay resto */
	//	b2Body* c;
	//	if ( (c=b->GetNext()) && !b->GetMass() ){
	//		b2Fixture* f1 = b->GetFixtureList();

	//		for ( ; c ; c = c->GetNext()){
	//			worldManifold->pointCount = 0;
	//			/* If c is not static skip it */
	//			if (c->GetMass())
	//				continue;
	//			/* If both are part of terrain skip them */
	//			if ((static_cast<int*>(b->GetUserData()) == 0) &&
	//				(static_cast<int*>(c->GetUserData()) == 0) )
	//					continue;

	//			if ( !c->GetMass()){
	//				b2Fixture* f2 = c->GetFixtureList();
	//				
	//				/* poly vs poly */
	//				if( f1->GetType() == b2Shape::e_polygon && f2->GetType() == b2Shape::e_polygon ){
	//					b2CollidePolygons(	worldManifold,(b2PolygonShape*)f1->GetShape(),b->GetTransform(),
	//										(b2PolygonShape*)f2->GetShape(),c->GetTransform() );
	//				}

	//				/* circle vs circle */
	//				if( f1->GetType() == b2Shape::e_circle && f2->GetType() == b2Shape::e_circle){
	//					b2CollideCircles(	worldManifold,(b2CircleShape*)f1->GetShape(),b->GetTransform(),
	//										(b2CircleShape*)f2->GetShape(),c->GetTransform() );

	//				}

	//				/* poly vs circle */
	//				if( (f1->GetType() == b2Shape::e_circle && f2->GetType() == b2Shape::e_polygon) ||
	//					(f1->GetType() == b2Shape::e_polygon && f2->GetType() == b2Shape::e_circle)){
	//						if ( f1->GetType() == b2Shape::e_circle )
	//							b2CollidePolygonAndCircle(	worldManifold,(b2PolygonShape*)f2->GetShape(),c->GetTransform(),
	//										(b2CircleShape*)f2->GetShape(),b->GetTransform() );
	//						if ( f2->GetType() == b2Shape::e_circle )
	//							b2CollidePolygonAndCircle(	worldManifold,(b2PolygonShape*)f1->GetShape(),b->GetTransform(),
	//										(b2CircleShape*)f2->GetShape(),c->GetTransform() );

	//				}


	//				if (worldManifold->pointCount > 0 ){
	//					/* Si B es el terreno */
	//					if (static_cast<int*>(b->GetUserData()) == 0){
	//						Log::t("Solapamiento de estaticos: %d", 
	//								static_cast<GameElement*>(c->GetUserData())->getId());
	//						deletedFixtures.insert(std::make_pair((static_cast<GameElement*>(c->GetUserData())->getId()),0 ));
	//					}

	//					/* Si C es el terreno */
	//					if (static_cast<int*>(c->GetUserData()) == 0){
	//						Log::t("Solapamiento de estaticos: %d", 
	//								static_cast<GameElement*>(b->GetUserData())->getId());
	//						deletedFixtures.insert(std::make_pair((static_cast<GameElement*>(b->GetUserData())->getId()),0 ));
	//					}

	//					/* Si ninguno de los dos es terreno quito el ultimo */
	//					Log::t("Solapamiento de estaticos: %d", 
	//							static_cast<GameElement*>(b->GetUserData())->getId());
	//					deletedFixtures.insert(std::make_pair((static_cast<GameElement*>(b->GetUserData())->getId()),0 ));

	//					worldManifold->pointCount = 0;
	//				}
	//			}
	//		}
	//	}
	//}

	//std::map<int,int>::iterator iterator = deletedFixtures.begin();
	//for ( ; iterator != deletedFixtures.end(); iterator++) {
	//	Log::i("Eliminando objeto de id: %d, por encontrarse superpuesto",
	//			iterator->first);
	//	this->deleteBody(iterator->first);
	//}

}


void GameEngine::deleteBody(int id){

	std::map<int,Body*>::iterator iterator;
	iterator = this->gameBodies->find(id);
	this->myWorld->DestroyBody(iterator->second->body);
	this->gameBodies->erase(iterator);
	this->gameLevel->removeEntity(id);

}


/*
id = worm_id
weaponid = id del arma
<x , y> = angulo del disparo
action = accion a ejecutar
*/
void GameEngine::applyAction2Element(int id, int weaponid, float x, float y, Movement action, int intensidad){

	std::map<int,GameElement*> copy = this->gameLevel->getEntities();
	GameElement* myWorm = copy[id];

	//printf("\n looking for worm %d and located worm: %d", id, myWorm->getId() );
	switch (action){
		case MOVE_RIGHT:
			static_cast<Worm*>(myWorm)->moveRight();
			break;
		case MOVE_LEFT:
			static_cast<Worm*>(myWorm)->moveLeft();
			break;
		case JUMP:
			static_cast<Worm*>(myWorm)->jump();
			break;
		case JUMP_RIGHT:
			static_cast<Worm*>(myWorm)->jumpRight();
			break;
		case JUMP_LEFT:
			static_cast<Worm*>(myWorm)->jumpLeft();
			break;
		case MOVE_STOP:
			static_cast<Worm*>(myWorm)->stop();
			break;
		case WITH_WEAPON_LEFT:
			static_cast<Worm*>(myWorm)->weaponedLeft();
			break;
		case WITH_WEAPON_RIGHT:
			static_cast<Worm*>(myWorm)->weaponedRight();
			break;
		case DO_SHOOT:
			printf("\nGet a DO_SHOOT");
			animateWeapon(weaponid, id, x, y, intensidad);
			break;
	}


	return;

}


void GameEngine::stopPlayer( std::string pl){

	this->gameLevel->stopWormsFromPlayer(pl);

}



// Solo se ejecuta si recibo la accion DO_SHOOT
void GameEngine::animateWeapon(int weaponid, int wormid, float angle_x, float angle_y, int intensidad){



	//Crea el arma en el modelo
	float xworm = this->gameLevel->getEntityByID(wormid)->getPosition().first;
	float yworm = this->gameLevel->getEntityByID(wormid)->getPosition().second;

	GameElement* myWeapon;

	int elementId = this->getWeaponUniqueId(); //QUE PASA CON EL ATAQUE AEREO QUE SON VARIOS??

	Missile* aMissile = MissileFactory::getInstance()->getMissile(weaponid,elementId);
	aMissile->setPosition(pair<float,float>(xworm,yworm));
	aMissile->setStartTime(this->myTimer.elapsed());


	Missile2d* aMissile2d = Missile2dFactory::getInstance()->getMissile(weaponid,WEAPON,xworm + angle_x, yworm, angle_x, angle_y, intensidad, this->myWorld, aMissile);
	aMissile->setBody(aMissile2d);

	this->gameLevel->addEntity(aMissile);
	this->gameBodies->insert(std::make_pair<int,Body*>(elementId,aMissile2d));


	
}


void GameEngine::doExplosion(b2Vec2 removalPosition, int removalRadius){

	poly_t* explosion = new poly_t();
	float x0 = -500.0f ,y0 = -500.0f;
	float x,y;
	*explosion = this->makeConvexRing(removalPosition, removalRadius, 16);
			

	list <poly_t*>* resultado = new list<poly_t*>();
	
	for(list<poly_t*>::iterator it = this->gameLevel->myPol->begin(); it != this->gameLevel->myPol->end(); it++){
			list <poly_t>* output = new list<poly_t>();
			boost::geometry::difference(*(*it), *explosion, *output);
			for(list<poly_t>::iterator it2 = output->begin(); it2 != output->end(); it2++){
					resultado->push_back(&(*it2));
			}

	}
	this->gameLevel->myPol->clear();
	this->gameLevel->myPol = resultado;

	for(std::vector<b2Body*>::iterator it = this->gameLevel->myTerrain.begin(); it != this->gameLevel->myTerrain.end(); it++){
			this->myWorld->DestroyBody(*it);
	}

	this->gameLevel->myTerrain.clear();

	//Genero nuevos bodys por cada componente conexa que quedo (chain)
	for(std::list<poly_t*>::iterator it = resultado->begin(); it != resultado->end(); it++){
			b2BodyDef* bd = new b2BodyDef();
			b2Vec2* vs = new b2Vec2[(*it)->outer().size()];
			int i = 0;

			for(vector<point>::iterator it2 = (*it)->outer().begin(); it2 != (*it)->outer().end(); it2++){
					vs[i].Set((*it2).get<0>(),(*it2).get<1>());
					i++;
			}

			b2ChainShape shape;
			shape.CreateLoop(vs,i);
			b2Body* tierra = this->myWorld->CreateBody(bd);
			
			//Defino propiedades del terreno
			b2FixtureDef myFixtureDef;
			myFixtureDef.friction=0.999;
			myFixtureDef.userData = ( (void*) UD_TERRAIN );
			myFixtureDef.shape = &shape;

			tierra->CreateFixture(&myFixtureDef);
			this->gameLevel->myTerrain.push_back(tierra);
	}




}


poly_t GameEngine::makeConvexRing(b2Vec2 position, float radius, int vertices)
{
	poly_t convexRing;
	const float theta = boost::math::constants::two_pi<float>() / static_cast<float>(vertices);

	float c = std::cos(theta);
	float s = std::sin(theta);

	float t = 0.0f;
	float y = 0.0f;
	float x = radius;
	for (float i = 0; i < vertices; i++)
	{
		float v_x = x + position.x;
		float v_y = y + position.y;
		bg::append(convexRing, point(v_x, v_y));

		t = x;
		x = c * x - s * y;
		y = s * t + c * y;
	}

	return convexRing;
}