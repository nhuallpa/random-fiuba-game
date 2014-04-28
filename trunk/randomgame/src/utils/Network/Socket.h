#ifndef SOCKET_H_
#define SOCKET_H_
#define WIN32_LEAN_AND_MEAN

#include <stdio.h>


#include <WinSock2.h>
#include <WS2tcpip.h>
#include "Messages.h"
#include <string>
#include <vector>

#define MAX_MESSAGE_SIZE 4096

// Link with ws2_32.lib
#pragma comment(lib, "Ws2_32.lib")


typedef std::string Player;

typedef struct {
	int wormid;
	int action; //
	int x; // X,Y alreaded passed to view coords.
	int y; //
} Playable;

typedef struct{
	Playable play;
	Player playerID;
	Messages type;
} Datagram;


class Socket
{
public:
	Socket ();
	Socket (uint16_t port);

	// Socket (const Socket&) = delete;
	// Socket (Socket&&) noexcept;
	
	
	// Socket& operator= (const Socket&) = delete;
	// Socket& operator= (Socket&&) noexcept;
	~Socket ();

	Socket init();
	void connect2 (std::string hostname, uint16_t port);
	bool sendmsg(Messages type, std::vector<uint8_t> datos);
	bool sendmsg(Datagram msg);
	bool rcvmsg(Datagram &msg);
	bool rcvmsg(Messages &type, std::vector<uint8_t> &datos);

	void setListen (int tamCola);
	void setRcvTimeout (long sec, long usec);
	void setSendTimeout (long sec, long usec);
	void setKeepAlive ();

	Socket aceptar ();
	int extraerFd ();
	int getFD();

private:
	bool usable;
	int fd;
};

#endif /* SOCKET_H_ */
