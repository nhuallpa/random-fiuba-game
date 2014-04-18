#pragma once

#ifndef __CLIENTE_H__
#define __CLIENTE_H__


#include "controlador/GameController.h"
#include "../Servidor/Servidor.h"
#include "vista/GameViewBuilder.h"



#include "controlador\Contracts\Contract.h"


// todo: cambiar TICK_INTERVAL por  DELAY_TIME y recuperar fps del yaml
//const int FPS = 60;
//const int DELAY_TIME = 1000.0f / FPS;

//#define TICK_INTERVAL    15

static Uint32 next_time;

class Cliente : public Contract{

	private:
		//TODO @future: Going to need a socket conn;

		bool begin();		// Inicia el VistaJuego y ControladorJuego
		void loop(void);
		GameLevel cLevel;
		GameController cController;
		bool connect2server(Servidor* server);
		Servidor* server;

		Uint32 time_left(void);

		Uint32 getTickInterval();


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