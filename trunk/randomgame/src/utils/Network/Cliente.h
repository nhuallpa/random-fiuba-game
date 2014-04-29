#ifndef CLIENTE_H_
#define CLIENTE_H_

#include "Socket.h"
#include "Messages.h"
#include "Thread.h"
#include "Condition.h"

#include <string>
#include <vector>
#include <list>




class Cliente {
public:
	Cliente();
	Cliente(char* ip, int port);
	~Cliente();

	bool serverAlive();

	static int keepalive(void* data);
	static int notifyLocalUpdates(void* data);
	static int applyNetworkChanges(void* data);

private:
	Socket input;
	Socket output;

	Player pl;

	// Se usa para controlar el timeout de los sockets
	time_t timeInicial;
	bool srvStatus;

	Mutex m;
	Condition somethingToTell;

	size_t revision;
	std::vector<Playable> localChanges;
	std::vector<Playable> networkChanges;

	void getRemoteWorld();
	int sendMsg(Messages type, std::vector<uint8_t> buffer);
	int sendDatagram(Datagram msg);
	int login();


};

typedef struct{
	Cliente* cli;
	Socket clientO;
	Socket clientI;
	char p[15];
} threadData;

#endif /* CLIENTE_H_ */
