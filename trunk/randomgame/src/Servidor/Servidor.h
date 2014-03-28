#pragma once

#include ".\modelo\GameEngine.h"



class Servidor{

	private:
		GameEngine gameEngine;
		//TODO @future Going to run over a socket;

		bool begin();
		void loop();

	public:
		Servidor();
		virtual ~Servidor();

		bool run(void);
		void destroyWorld();
		GameEngine getGameEngine();
		GameLevel getLevel();

};
