#ifndef SOCKET_H_
#define SOCKET_H_
#define WIN32_LEAN_AND_MEAN

#include <stdio.h>


#include <WinSock2.h>
#include <WS2tcpip.h>
#include "Messages.h"
#include <string>
#include <vector>


// Link with ws2_32.lib
#pragma comment(lib, "Ws2_32.lib")


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
	bool rcvmsg(Messages &type, std::vector<uint8_t> &datos);

	void setListen (int tamCola);
	void setRcvTimeout (long sec, long usec);
	void setSendTimeout (long sec, long usec);
	void setKeepAlive ();

	Socket aceptar ();
	int extraerFd ();

private:
	bool usable;
	int fd;
};

#endif /* SOCKET_H_ */
