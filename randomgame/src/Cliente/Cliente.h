#pragma once

#ifndef __CLIENTE_H__
#define __CLIENTE_H__


#include "controlador/GameController.h"
#include "../Servidor/Servidor.h"
#include "vista/GameViewBuilder.h"
#include <SDL2_framerate.h>
#include "vista\Bootstrap.h"
#include "vista\Activity.h"
#include "vista\GameActivity.h"


#include "controlador\Contracts\Contract.h"


// todo: cambiar TICK_INTERVAL por  DELAY_TIME y recuperar fps del yaml
//const int FPS = 60;
//const int DELAY_TIME = 1000.0f / FPS;

//#define TICK_INTERVAL    15

static Uint32 next_time;

class Cliente : public Contract{

	private:
		//TODO @future: Going to need a socket conn;
		
		GameLevel cLevel;
		
		/**Inicializador de componentes de la vista*/
		Bootstrap bootstrap;

		/**Activity que manerja la pantalla actual de la vista*/
		Activity* currentActivity;

		/**Controlador de eventos y estados*/
		GameController cController;
		
		bool connect2server(Servidor* server);
		Servidor* server;

		Uint32 time_left(void);

		Uint32 getTickInterval();

		/**Inicia el VistaJuego y ControladorJuegon*/
		bool begin();		
		void loop(void);

		void runGame();
		void stopGame();
		void iniGame();

	public:
		Cliente(Servidor* server);

		virtual ~Cliente(void);

		bool run();

		void destroyWorld();

		

};

#endif