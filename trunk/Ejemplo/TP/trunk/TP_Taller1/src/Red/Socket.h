#ifndef SOCKET_H_
#define SOCKET_H_

#include "Red/TipoMensaje.h"
#include <string>
#include <vector>

namespace Red {

class Socket
{
public:
	Socket () noexcept;
	Socket (uint16_t puerto);
	static Socket crear();

	Socket (const Socket&) = delete;
	Socket (Socket&&) noexcept;
	Socket& operator= (const Socket&) = delete;
	Socket& operator= (Socket&&) noexcept;
	~Socket ();

	void conectar (std::string hostname, uint16_t puerto);

	bool enviar (Red::TipoMensaje tipo, std::vector<uint8_t> datos);
	bool recibir (Red::TipoMensaje &tipo, std::vector<uint8_t> &datos);

	void setListen (int tamCola);
	void setTimeoutRecibir (long sec, long usec);
	void setTimeoutEnviar (long sec, long usec);
	void setKeepAlive ();

	Socket aceptar ();
	int extraerFd ();

private:
	bool valido;
	int fd;
};

} /* namespace Red */
#endif /* SOCKET_H_ */
