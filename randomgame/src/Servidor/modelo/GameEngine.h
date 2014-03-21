#pragma once

#include "GameLevel.h"

class GameEngine {

	private:
		GameLevel gameLevel;
		//GameLoop gameLoop;
		//ThreadRcv* pRcvThread;

	public:
		GameEngine();
		
		virtual ~GameEngine();

		//bool iniciarEscenario(SocketServidor* pSocket);
		//bool beginRcv(SocketServidor* pSocket);

		bool initWorld();
		bool loop();

		//void endRcvPhase(void);
		GameLevel getLevel();
		int howManyPlayers(void);
};
