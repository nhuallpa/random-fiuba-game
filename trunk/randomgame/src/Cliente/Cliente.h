#pragma once

#ifndef __CLIENTE_H__
#define __CLIENTE_H__


#include "controlador/GameController.h"
#include "vista/GameViewBuilder.h"
#include <SDL2_framerate.h>
#include "vista\Bootstrap.h"
#include "vista\Activity.h"
#include "vista\GameActivity.h"
#include "controlador\Contracts\OnMovementListener.h"
#include <SDL2_framerate.h>
#include "../utils/Network/Socket.h"
#include "../utils/Network/Messages.h"
#include "../utils/Network/Thread.h"
#include "../utils/Network/Condition.h"

#include "../utils/Log.h"
#include <string>
#include <iostream>
#include <ctime>


#include <string>
#include <vector>
#include <list>



// todo: cambiar TICK_INTERVAL por  DELAY_TIME y recuperar fps del yaml
//const int FPS = 60;
//const int DELAY_TIME = 1000.0f / FPS;

//#define TICK_INTERVAL    15

static Uint32 next_time;
class Cliente;
typedef struct {
	Cliente * cli;
	Socket clientO;
	Socket clientI;
	char p[15];
} threadData;


class Cliente : public OnMovementListener{

	private:
		//TODO @future: Going to need a socket conn;
		
		//GameLevel cLevel;
		
		/**Inicializador de componentes de la vista*/
		Bootstrap bootstrap;

		/**Activity que manerja la pantalla actual de la vista*/
		Activity* currentActivity;

		
		GameActivity* gameActivity;

		/**Controlador de eventos y estados*/
		GameController cController;
		
		GameDomain domain;

		//bool connect2server(Servidor* server);
		//Servidor* server;

		Uint32 time_left(void);

		Uint32 getTickInterval();

		/**Inicia el VistaJuego y ControladorJuegon*/
		bool begin();		
		void loop(void);

		void runGame();

		Socket input;
		Socket output;

		Player pl;

		// Se usa para controlar el timeout de los sockets

		bool srvStatus;

		Mutex m;
		Mutex n;
		Condition somethingToTell;
		Condition somethingToUpdate;

		size_t revision;
		std::vector<Playable> localChanges;
		std::vector<Playable> networkChanges;

		void getRemoteWorld();
		int sendMsg(Messages type, std::vector<uint8_t> buffer);
		int sendDatagram(Datagram msg);
		int login();

		/* Data for threading**/
		threadData data;


	public:
		//Cliente(Servidor* server);
		Cliente(std::string playerID, char* ip, int port);
		
		virtual ~Cliente(void);

		bool run();

		void destroyWorld();

		void OnMovement(MovementEvent e);

		bool serverAlive();
	
		//Listen changes in the network
		static int netListener(void* data);

		//notify over the network for a local change on the client
		static int notifyLocalUpdates(void* data);

		//Apply the changes that we receive on listen state
		static int applyNetworkChanges(void* data);

		static int clientSideEmulation(void* data);

		void addLocalMovementFromView(Playable p);


		void lockLocalMutex();

		void unlockLocalMutex();

		void lockNetworkMutex();

		void unlockNetworkMutex();

		void addLocalChange(Playable p);

		bool updateModel(Playable p);

		void signalLocalChange();

		void signalNetworkChange();

		GameElement getElementFromPlayable(Playable p);


};


#endif