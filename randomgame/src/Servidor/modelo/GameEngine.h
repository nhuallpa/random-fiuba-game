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

class GameEngine {

	private:
		GameLevel gameLevel;
		float timeStep;      
		int velocityIterations;   
		int positionIterations;
		//ThreadRcv* pRcvThread;
		TerrainProcessor* aTerrainProcessor;
		std::list<Body*> bodies;
		b2World* myWorld;

		Body* lookForABody();
		ContactListener* myContactListener;
		std::list<Body*> gameBodies;
		void floodWorld();

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
