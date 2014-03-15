#include "base.h"

#include "Log/Suceso.h"
#include "Red/Cabecera.h"
#include <netinet/in.h>
#include <cstring>

namespace Red {

static std::string errnoParse()
{
	int errno_save = errno;
	return std::string("errno ") + std::to_string(errno_save) + ": " + strerror(errno_save) + ".";
}

static bool enviarBase (int fd, std::vector<uint8_t> datos, std::string errmsg)
{
	size_t intentos = 0;
	size_t base = 0;
	size_t aEnviar = datos.size();
	while (aEnviar != 0) {
		int bytes = send(fd, &datos[base], aEnviar, 0);
		if (bytes == -1) {
			if (errno == EINTR) {
				continue;
			} else if (errno == EAGAIN || errno == EWOULDBLOCK) {
				if (intentos < 3) {
					intentos += 1;
					sleep(10);
					continue;
				}
			}
			throw Log::Suceso(Log::ERROR, errmsg + " " + errnoParse());
		} else if (bytes == 0) {
			return false;
		} else {
			base += bytes;
			aEnviar -= bytes;
		}
	}
	return true;
}

bool enviar (int fd, Red::TipoMensaje tipo, std::vector<uint8_t> datos)
{
	if (datos.empty()) {
		throw Log::Suceso(Log::DEBUG, "Se intenta mandar un mensaje vacio.");
	}

	size_t buffer_len = datos.size();
	Red::Cabecera cabecera(tipo, buffer_len);
	if (!enviarBase(fd, cabecera.aVector(), "Fallo al enviar cabecera.")) {
		return false;
	}
	if (!enviarBase(fd, datos, "Fallo al enviar datos.")) {
		return false;
	}
	return true;
}


static bool recibirBase (int fd, std::vector<uint8_t> &datos, size_t tamEsperado, std::string errmsg)
{
	std::vector<uint8_t> datosRetorno(tamEsperado);
	size_t intentos = 0;
	size_t base = 0;
	size_t aRecibir = tamEsperado;
	while (aRecibir != 0) {
		int bytes = recv(fd, &datosRetorno[base], aRecibir, 0);
		if (bytes == -1) {
			if (errno == EINTR) {
				continue;
			} else if (errno == EAGAIN || errno == EWOULDBLOCK) {
				if (intentos < 3) {
					intentos += 1;
					sleep(10);
					continue;
				}
			}
			throw Log::Suceso(Log::ERROR, errmsg + " " + errnoParse());
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

bool recibir (int fd, Red::TipoMensaje &tipo, std::vector<uint8_t> &datos)
{
	std::vector<uint8_t> cabeceraVector;
	if (!recibirBase(fd, cabeceraVector, Red::Cabecera::tamVector(),
	                 "Fallo al recibir cabecera.")) {
		return false;
	}
	Red::Cabecera cabecera(cabeceraVector);
	if (!recibirBase(fd, datos, cabecera.longitud, "Fallo al recibir datos.")) {
		return false;
	}
	tipo = cabecera.idMensaje;
	return true;
}

} /* namespace Red */
