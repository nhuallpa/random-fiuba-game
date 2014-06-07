#pragma once

#ifndef __GAMEENGINE__ 
#define __GAMEENGINE__

#include "GameLevel.h"
#include <list>
#include "Physics\ContactListener.h"
#include "Physics\Body.h"
#include "Physics\Bodies\Cuadrado.h"
#include "Physics\Bodies\Circle.h"
#include "Physics\Bodies\Hexagon.h"
#include "Physics\Bodies\Triangulo.h"
#include "Physics\Bodies\Pentagon.h"
#include "Physics\Bodies\Water.h"
#include "Physics\Weapon2d.h"
#include "TerrainProcessor.h"
#include "Entities\MissileFactory.h"
#include "..\modelo\Physics\Bodies\Missiles\Missile2dFactory.h"
#include  "Entities\Missile.h"
#include "../../utils/Timer.h"

#include <set>
#include <utility>



class GameEngine {

	private:
		/*std::set<fixturePair> m_fixturePairs;*/
		GameLevel* gameLevel;
		float timeStep;      
		int velocityIterations;   
		int positionIterations;
		//ThreadRcv* pRcvThread;
		TerrainProcessor* aTerrainProcessor;

		//map de las explosiones del mapa
		std::vector<Explosion> mapExplosions;
		std::queue<Explosion> lastExplosions;

		b2World* myWorld;
		Water* water;
		MissileFactory* missileFactory;
		Missile2dFactory* missile2dFactory;

		Body* lookForABody();
		ContactListener myContactListener;

		std::map<int, Body*>* gameBodies;
		std::map<int, Body*>* gameWeapons;

		void floodWorld();
		void animateContacts();
		bool findIntersectionOfFixtures(b2Fixture* fixtureA, b2Fixture* fixtureB);
		bool intersectionWithWater(b2Fixture* fixtureA);
		void updateBodyPositions();
		void deleteBody(int id);
		int weaponUniquedId;
		//Agarra los worms de un jugador y los pone como activos
		//Para mi lo mejor es armar una clase GamePlayer que tenga la lista de wormsID que posee.
		bool setWormsFromPlayerAsActive(std::string playerID);

	public:

		GameEngine();

		Timer myTimer;

		void addExplosion(Explosion e){ this->mapExplosions.push_back(e); }
		void enqueueExplosion(Explosion e){ this->lastExplosions.push(e); }

		std::vector<Explosion> getMapExplosions(){ return this->mapExplosions; }

		bool getExplosion(Explosion e);

		void stopPlayer( std::string pl);
		
		virtual ~GameEngine();
		int getWeaponUniqueId();
		void addWeapon(int id, b2Body* body);

		// Pone los worms en el mapa y se los guarda al player id (persiste en el yaml)
		bool placeInitialWorms(std::string playerID);

		//Si el jugador no existe lo crea sino lo marca como activo y activa sus worms
		bool registerPlayer(std::string playerID);

		//carga los worms del jugador
		void loadWormsFromPlayer(std::string playerID);

		//pone el jugador como desconectado y detiene sus worms
		bool disconnectPlayer(std::string playerID);

		//La nueva struct del yaml debe terner player y sus worms.

		void animateWormsFromPlayer(std::string playerID);

		//TODO @aliguo
		// Devuelve todos los elementos "Playable" del mundo
		void getPlayableWorld();

		//receives a Playable element and apply it to the model
		// First get the worm ID from the player, then apply the movement
		// and lately step into the world and broadcast
		bool applyPlayable2Model();

		void applyAction2Element(int id, int weaponid, float x, float y, Movement action, int intensidad);

		bool step();

		float getTimeStep ();
		//bool iniciarEscenario(SocketServidor* pSocket);
		//bool beginRcv(SocketServidor* pSocket);

		bool initWorld();
		void reInitWorld();
		bool loop();

		// Create simple world
		void animateWorld();
		void animateBodies();
		void animateJoints();
		void animateWeapon(int weaponid, int wormid, float angle_x, float angle_y, int intensidad);

		std::map<int,Body*>* getGameBodies(){ return this->gameBodies;}

		// Le pasa el nivel completo al
		GameLevel* getLevel();
		int howManyPlayers(void);


		int getUpdateStep(){return this->getLevel()->updateStep;}
		void incrementUpdateStep(){ this->getLevel()->updateStep += 1; }
		void resetUpdateStep(){ this->getLevel()->updateStep = 0; }

		
};


#endif /*__GAMEENGINE__*/
