#pragma once

#include "GameLevel.h"
#include <list>
#include "Physics\ContactListener.h"
#include "Physics\Body.h"

class GameEngine {

	private:
		GameLevel gameLevel;
		float timeStep;      
		int velocityIterations;   
		int positionIterations;
		//ThreadRcv* pRcvThread;

		std::list<Body*> bodies;
		b2World* myWorld;

		Body* lookForABody();
		ContactListener contactListener;
		std::list<Body*> gameBodies;

	public:
		GameEngine();
		virtual ~GameEngine();

		bool step();
		float getTimeStep ();
		//bool iniciarEscenario(SocketServidor* pSocket);
		//bool beginRcv(SocketServidor* pSocket);

		bool initWorld();
		bool loop();

		// Create simple world
		void animateWorld();

		
		void animateBodies();

		void animateJoints();




		// Le pasa el nivel completo al
		GameLevel getLevel();
		int howManyPlayers(void);
};
