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

		Body* lookForABody();
		ContactListener contactListener;

	public:
		GameEngine();
		
		virtual ~GameEngine();

		bool step();
		float getTimeStep ();
		//bool iniciarEscenario(SocketServidor* pSocket);
		//bool beginRcv(SocketServidor* pSocket);

		bool initWorld();
		bool loop();

		void animateWorld();
		void animateBodies();
		void animateJoints();

		b2World* myWorld;
		//Lista de cuerpos que se va a recorrer y hacer vivir en
		//cada step del simulador.




		//void endRcvPhase(void);
		GameLevel getLevel();
		int howManyPlayers(void);
};
