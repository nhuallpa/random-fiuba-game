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

	public:
		GameEngine();
		virtual ~GameEngine();



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
