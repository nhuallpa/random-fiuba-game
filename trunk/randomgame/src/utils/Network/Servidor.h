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
	int playerId;
	std::string name;
} Player;

class Servidor {
public:
	Servidor();
	Servidor(int nroPuerto, size_t cantJugadores);
	~Servidor();

	void push (Playable change);

	void esperarLlamadas();
	bool allConnected() const;
	void esperarUserDelta ();

	static int messageManager(void* data);
	static void notifyReject(Socket& fdCli);

private:
	Socket input;
	Socket output;
	size_t cantJugadores;

	// Lista de clientes conectados y sus file descriptors asociados
	typedef std::map<std::string, std::pair<int,int>> Players;
	Atomic<Players> playerList;
	Queue<Playable> deltas;

	
	void wait4Connections();

	void sendHeartBeat(Player playerId, Messages type);
	
	void broadcastMsg(Playable change);
	void enviarMensaje(Player playerId, std::vector<uint8_t> buffer);
	void wait4Updates(Player playerId);
	void desconectar(Player playerId);
};

#endif /* SERVIDOR_H_ */
