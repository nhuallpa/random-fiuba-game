#include "Socket.h"

#include "Log/Suceso.h"
#include "Red/base.h"
#include "Red/Cabecera.h"
#include <arpa/inet.h>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <netdb.h>
#include <netinet/in.h>

namespace Red {

Socket::Socket() noexcept
	: valido(false)
	, fd()
{
}

Socket::Socket (uint16_t puerto)
	: valido(false)
	, fd()
{
	*this = Socket::crear();

	// Seteo la direccion del servidor
	struct sockaddr_in dirServer;
	bzero((char *) &dirServer, sizeof(dirServer));
	dirServer.sin_family = AF_INET;
	dirServer.sin_port = htons(puerto);
	dirServer.sin_addr.s_addr = INADDR_ANY;

	// Lo enlazo al puerto establecido
	if (bind(fd, (struct sockaddr*)&dirServer, sizeof(dirServer)) == -1) {
		throw Log::Suceso(Log::FATAL, "No se pudo enlazar el socket de salidas del servidor con el puerto establecido.");
	}
}

Socket Socket::crear()
{
	Socket retval;
	retval.valido = true;
	retval.fd = socket(AF_INET, SOCK_STREAM, 0);
	if (retval.fd == -1) {
		throw Log::Suceso(Log::FATAL, "No se pudo inicializar el socket.");
	}
	return retval;
}

Socket::Socket (Socket&& origen) noexcept
	: valido(origen.valido)
	, fd(origen.fd)
{
	origen.valido = false;
}

Socket& Socket::operator= (Socket&& origen) noexcept
{
	using std::swap;
	swap(origen.valido, valido);
	swap(origen.fd, fd);
	return *this;
}

Socket::~Socket()
{
	if (valido) {
		close(fd);
	}
}

void Socket::conectar (std::string hostname, uint16_t puerto)
{
	struct hostent *server = gethostbyname(hostname.c_str());
	if (server == NULL) {
		throw Log::Suceso(Log::FATAL, "No se encontro el host.");
	}

	struct sockaddr_in dirServer;
	bzero((char *) &dirServer, sizeof(dirServer));
	dirServer.sin_family = AF_INET;
	dirServer.sin_port = htons(puerto);
	bcopy((char *)server->h_addr, (char *)&dirServer.sin_addr.s_addr, server->h_length);

	if (connect(fd, (struct sockaddr*)&dirServer, sizeof(dirServer)) == -1 ) {
		throw Log::Suceso(Log::FATAL, "No se pudo conectar socket.");
	}
}

bool Socket::enviar (Red::TipoMensaje tipo, std::vector<uint8_t> datos)
{
	return Red::enviar(fd, tipo, datos);
}

bool Socket::recibir (Red::TipoMensaje &tipo, std::vector<uint8_t> &datos)
{
	return Red::recibir(fd, tipo, datos);
}

void Socket::setListen (int tamCola)
{
	if (::listen(fd, 4) == -1) {
		throw Log::Suceso(Log::FATAL, "No se pudo setear el tamanio maximo de la cola de conexiones pendientes en el puerto.");
	}
}

void Socket::setTimeoutRecibir (long sec, long usec)
{
	struct timeval timeout;
	timeout.tv_sec = sec;
	timeout.tv_usec = usec;

	if (setsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout)) == -1) {
		Log::Suceso(Log::ERROR, "Fallo seteo del timeout en socket.");
	}
}

void Socket::setTimeoutEnviar (long sec, long usec)
{
	struct timeval timeout;
	timeout.tv_sec = sec;
	timeout.tv_usec = usec;

	if (setsockopt(fd, SOL_SOCKET, SO_SNDTIMEO, (char *)&timeout, sizeof(timeout)) == -1) {
		Log::Suceso(Log::ERROR, "Fallo seteo del timeout en socket.");
	}
}

void Socket::setKeepAlive ()
{
	int iOption = 1;
	if (setsockopt(fd, SOL_SOCKET, SO_KEEPALIVE, (const char *) &iOption,  sizeof(int)) == -1) {
		Log::Suceso(Log::ERROR, "Fallo seteo de la opcion keepalive en socket.");
	}
}

Socket Socket::aceptar ()
{
	Socket retval;

	struct sockaddr_in dirCli;
	socklen_t dirCliSize = sizeof (dirCli);
	retval.fd = accept(fd, (struct sockaddr*) &dirCli, &dirCliSize);

	if (retval.fd == -1) {
		auto msg = "No se pudo aceptar la llamada de salida en el servidor.";
		throw Log::Suceso(Log::ERROR, msg);
	}
	printf("Recibida conexion %i de %s puerto %d\n", retval.fd,
	       inet_ntoa(dirCli.sin_addr), ntohs(dirCli.sin_port));

	return retval;
}

int Socket::extraerFd ()
{
	valido = false;
	return fd;
}

} /* namespace Red */
