#ifndef SERVIDOR_H_
#define SERVIDOR_H_

#pragma once

#include <map>
#include <vector>
#include <list>
#include <string>

#include "Socket.h"
#include "Thread.h"
#include "Condition.h"

#include ".\modelo\GameEngine.h"



class Servidor{

	private:
		GameEngine gameEngine;
		//TODO @future Going to run over a socket;

		bool begin();
		void loop();

		Socket input;
		Socket output;
		size_t cantJugadores;
		size_t jugadoresConectados;

		// Lista de clientes conectados y sus file descriptors asociados
		typedef std::map<std::string, std::pair<int,int>> Players;
		Players pList;

		//This really is client side requested changes/actions
		std::vector<Playable> changes;

		// This is all the changes after apply all client side actions, THIS
		// MUST be propagated to all the clients.
		std::vector<Playable> worldChanges;	

		void sendHeartBeat(Player playerId, Messages type);
	
		void broadcastMsg(Playable change);
		void enviarMensaje(Player playerId, std::vector<uint8_t> buffer);
		void wait4Updates(Player playerId);
		void disconnect(std::string playerId);


	public:
		Servidor();
		~Servidor();


		Servidor(int nroPuerto, size_t cantJugadores);


		bool allConnected() const;
		void esperarUserDelta ();
	
		Mutex lock;
		Condition canUpdate;
		Mutex netlock;
		Condition canBroadcast;

		void waitConnections();
	
		static int broadcastMessages(void* data);
		static int updating(void* data);
		static int initClient(void* data);
		static void notifyReject(Socket& fdCli);
		static int wait4Connections(void* data);


		bool run(void);
		void destroyWorld();
		GameEngine getGameEngine();
		GameLevel getLevel();

};

typedef struct{
	Servidor* srv;
	Socket clientO;
	Socket clientI;
	char p[15];
} threadData;

#endif /* SERVIDOR_H_ */