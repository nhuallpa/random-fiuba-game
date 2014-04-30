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
#include "TerrainProcessor.h"
#include <set>
#include <utility>



class GameEngine {

	private:
		/*std::set<fixturePair> m_fixturePairs;*/
		GameLevel gameLevel;
		float timeStep;      
		int velocityIterations;   
		int positionIterations;
		//ThreadRcv* pRcvThread;
		TerrainProcessor* aTerrainProcessor;

		b2World* myWorld;
		Water* water;

		Body* lookForABody();
		ContactListener myContactListener;
		std::map<int, Body*> gameBodies;
		void floodWorld();
		void animateContacts();
		bool findIntersectionOfFixtures(b2Fixture* fixtureA, b2Fixture* fixtureB);
		bool intersectionWithWater(b2Fixture* fixtureA);
		void updateBodyPositions();
		void deleteBody(int id);

		//TODO
		//Agarra los worms de un jugador y los pone como activos
		//Para mi lo mejor es armar una clase GamePlayer que tenga la lista de wormsID que posee.
		bool setWormsFromPlayerAsActive(std::string playerID);

	public:
		GameEngine();
		virtual ~GameEngine();

		
		//TODO: @BAUTI
		// Pone los worms en el mapa y se los guarda al player id (persiste en el yaml)
		bool placeInitialWorms(std::string playerID);

		//Si el jugador no existe lo crea sino lo marca como activo y activa sus worms
		bool registerPlayer(std::string playerID);

		//carga los worms del jugador
		void loadWormsFromPlayer(std::string playerID);

		//pone el jugador como desconectado y detiene sus worms
		bool disconnectPlayer(std::string playerID);

		//La nueva struct del yaml debe terner player y sus worms.



		//TODO @aliguo
		// Devuelve todos los elementos "Playable" del mundo
		void getPlayableWorld();

		//receives a Playable element and appl it to the model
		bool applyPlayable2Model();




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


		// Le pasa el nivel completo al
		GameLevel getLevel();
		int howManyPlayers(void);
};


#endif /*__GAMEENGINE__*/
