#include "Socket.h"
#include <cstdio>
#include <cstring>
#include <string>
#include <iostream>
#include <windows.h>

Socket::Socket()
	: usable(false)
	, fd()
{
}

Socket::Socket (uint16_t port)
	: usable(false)
	, fd()
{
	//*this = Socket::init();
	WSAData wsaData;

    int error = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (error == SOCKET_ERROR)
    {
        std::cout << "Server: Winsock Failed to begin!\n";
        return;
    }
	std::cout << "Server: WinSocket Started Correctly!\n";

	this->usable = true;
	
	this->fd = socket(AF_INET, SOCK_STREAM, 0);

	if (this->fd == -1) {
		//Log::e("Couldn't open socket connection");
	}
	


	/* IP Address and connection info of the server A.K.A Destination */
	printf("Creando socket");
	struct sockaddr_in server_addr;
	//Set properties for the host
	//memset((char *) &server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port);
	server_addr.sin_addr.s_addr = INADDR_ANY;
	// Connect
	error = bind(this->fd, (struct sockaddr*)&server_addr, sizeof(server_addr));
	if ( error == -1) {
		printf("\nCouldn't bind server at specified address/port\n");
		printf("Error during bind: %s, code: %d", std::strerror(errno),WSAGetLastError());
		//Log::e("Couldn't bind server at specified address/port"); 
	}

	error = listen(this->fd, 5); // Listen for connections

    if (error == SOCKET_ERROR)
    {
        std::cout << "Server: Too deaf to listen...\n"; 
    }

    std::cout << "Server: Waiting for a client to connect ...\n"; // Just to keep us up to date





}

Socket Socket::init()
{
	Socket retval;

	WSAData wsaData;

    int error = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (error == SOCKET_ERROR)
    {
        std::cout << "Server: Winsock Failed to begin!\n";
        return 1;
    }
	std::cout << "Server: WinSocket Started Correctly!\n";
	retval.usable = true;
	
	retval.fd = socket(AF_INET, SOCK_STREAM, 0);

	if (retval.fd == -1) {
		//Log::e("Couldn't open socket connection");
	}
	return retval;
}

// Socket::Socket (Socket&& origen) noexcept
	// : usable(origen.usable)
	// , fd(origen.fd)
// {
	// origen.usable = false;
// }

// Socket& Socket::operator= (Socket&& origen) noexcept
// {
	// using std::swap;
	// swap(origen.usable, usable);
	// swap(origen.fd, fd);
	// return *this;
// }

Socket::~Socket(){
	if (usable) {
		closesocket(fd);
	}
}

void Socket::connect2(std::string hostname, uint16_t port)
{
	struct hostent *server = gethostbyname(hostname.c_str());
	if (server == NULL) {
		//Log::e("Couldn't find host: %s",hostname);
		printf("Couldn't find host: %s",hostname.c_str());
	}

	this->init();

	//Init server struct and its data
	struct sockaddr_in server_addr;
	memset((char *) &server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port);
	memcpy(	(char *)&server_addr.sin_addr.s_addr,
			(char *)server->h_addr,
			server->h_length
		);
	
	//Connect server
	if (connect(this->fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == SOCKET_ERROR ) {
		//Log::e("Couldn't connect to specified address/port: %s : %d",hostname,port);
		printf("Couldn't connect to specified address/port: %s : %d",hostname,port);
	}
}

bool Socket::sendmsg (Messages tipo, std::vector<uint8_t> datos)
{
	
	size_t intentos = 0;
	size_t base = 0;
	size_t aEnviar = datos.size();
	
	if (datos.empty()) {
		//Log::e("Sending empty message");
	}
	
	while (aEnviar != 0) {
		int bytes = send(fd, (char*)(&datos[base]), aEnviar, 0);
		if (bytes == -1) {
			if (errno == EINTR) {
				continue;
			} else if (errno == EAGAIN || errno == EWOULDBLOCK) {
				if (intentos < 3) {
					intentos += 1;
					Sleep(10);
					continue;
				}
			}
			//Log::e("Failed to send msg");
		} else if (bytes == 0) {
			return false;
		} else {
			base += bytes;
			aEnviar -= bytes;
		}
	}
	return true;	
	
}

bool Socket::rcvmsg (Messages &tipo, std::vector<uint8_t> &datos)
{
	// return Red::recibir(fd, tipo, datos);
	int tamEsperado = 10; //TODO
	std::vector<uint8_t> datosRetorno(tamEsperado);
	size_t intentos = 0;
	size_t base = 0;
	size_t aRecibir = tamEsperado;
	while (aRecibir != 0) {
		int bytes = recv(fd, (char*)(&datosRetorno[base]), aRecibir, 0);
		if (bytes == -1) {
			if (errno == EINTR) {
				continue;
			} else if (errno == EAGAIN || errno == EWOULDBLOCK) {
				if (intentos < 3) {
					intentos += 1;
					Sleep(10);
					continue;
				}
			}
			//Log::e("Failed to get data from remote host");
		} else if (bytes == 0) {
			return false;
		} else {
			base += bytes;
			aRecibir -= bytes;
		}
	}
	using std::swap;
	swap(datos, datosRetorno);
	return true;
	
}

void Socket::setListen (int tamCola)
{
	if (::listen(fd, 4) == -1) {
		// throw Log::Suceso(Log::FATAL, "No se pudo setear el tamanio maximo de la cola de conexiones pendientes en el port.");
	}
}

void Socket::setRcvTimeout (long sec, long usec)
{
	struct timeval timeout;
	timeout.tv_sec = sec;
	timeout.tv_usec = usec;

	if (setsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout)) == -1) {
		//Log::e("Couldn't set specified timeout");
	}
}

void Socket::setSendTimeout (long sec, long usec)
{
	struct timeval timeout;
	timeout.tv_sec = sec;
	timeout.tv_usec = usec;

	if (setsockopt(fd, SOL_SOCKET, SO_SNDTIMEO, (char *)&timeout, sizeof(timeout)) == -1) {
		
		//Log::e("Couldn't set specified timeout");
	}
}

void Socket::setKeepAlive ()
{
	int iOption = 1;
	if (setsockopt(fd, SOL_SOCKET, SO_KEEPALIVE, (const char *) &iOption,  sizeof(int)) == -1) {
		//Log::Suceso(Log::ERROR, "Fallo seteo de la opcion keepalive en socket.");
	}
}

Socket Socket::aceptar ()
{
	Socket retval;

	struct sockaddr_in dirCli;
	socklen_t dirCliSize = sizeof (dirCli);
	retval.fd = accept(this->fd, (struct sockaddr*) &dirCli, &dirCliSize);

	if (retval.fd == -1) {
		//auto msg = "No se pudo aceptar la llamada de salida en el servidor.";
		//throw Log::Suceso(Log::ERROR, msg);
	}
	printf("Recibida conexion %i de %s port %d\n", retval.fd,
	       inet_ntoa(dirCli.sin_addr), ntohs(dirCli.sin_port));

	return retval;
}

int Socket::extraerFd ()
{
	usable = false;
	return fd;
}
