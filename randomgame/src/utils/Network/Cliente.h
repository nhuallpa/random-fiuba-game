#ifndef CLIENTE_H_
#define CLIENTE_H_

#include "Socket.h"
#include "Messages.h"
#include "Thread.h"
#include <string>
#include <vector>
#include <list>

typedef struct {
	int wormid;
	int action;
} Playable;

typedef struct {
	std::string playerId;
} Player;

class Cliente {
public:
	Cliente();
	Cliente(char* ip, int port);
	~Cliente();

	bool alive();


private:
	Socket input;
	Socket output;

	Player pl;

	// Se usa para controlar el timeout de los sockets
	time_t timeInicial;


	std::list<Playable> localChanges;
	std::list<Playable> networkChanges;

	void esperarMensaje();
	void sendMsg(Messages type, std::vector<uint8_t> buffer);
};

typedef struct{
	Cliente* cli;
	Socket clientO;
	Socket clientI;
	Player p;
} threadData;

#endif /* CLIENTE_H_ */
