#pragma once
#include "controlador/GameController.h"
#include "vista/GameView.h"
#include "../Servidor/Servidor.h"

class Cliente{

	private:
		//TODO @future: Going to need a socket conn;

		bool begin();		// Inicia el VistaJuego y ControladorJuego
		void loop(void);
		GameLevel cLevel;
		GameView cView;
		GameController cController;
		bool connect2server(Servidor* server);
		Servidor* server;

		
	public:
		Cliente(Servidor* server);
		virtual ~Cliente(void);

		bool run();
		void destroyWorld();

};
