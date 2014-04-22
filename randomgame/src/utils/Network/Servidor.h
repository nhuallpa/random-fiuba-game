#ifndef SERVIDOR_H_
#define SERVIDOR_H_

#include <map>
#include <vector>

#include "Socket.h"
#include "Thread.h"
#include "Atomic.h"
#include "Queue.h"

typedef struct {
	int wormid;
	int action;
} Playable;




typedef struct {
	std::string playerId;
} Player;



class Servidor {
public:
	Servidor();
	Servidor(int nroPuerto, size_t cantJugadores);
	~Servidor();

	bool allConnected() const;
	void esperarUserDelta ();
	
	Mutex lock;
	Condition canUpdate;

	static int updating(void* data);
	static int initClient(void* data);
	static void notifyReject(Socket& fdCli);

private:
	Socket input;
	Socket output;
	size_t cantJugadores;

	// Lista de clientes conectados y sus file descriptors asociados
	typedef std::map<std::string, std::pair<int,int>> Players;
	Players pList;
	Queue<Playable> changes;

	
	void wait4Connections();

	void sendHeartBeat(Player playerId, Messages type);
	
	void broadcastMsg(Playable change);
	void enviarMensaje(Player playerId, std::vector<uint8_t> buffer);
	void wait4Updates(Player playerId);
	void desconectar(Player playerId);
};

typedef struct{
	Servidor* srv;
	Socket clientO;
	Socket clientI;
	Player p;
} threadData;

#endif /* SERVIDOR_H_ */
