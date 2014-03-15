/*
 * Cabecera.cpp
 *
 *  Created on: 14/11/2013
 *  Last Amended: 14/11/2013
 *      Author: natuchis
 */

#include "Cabecera.h"

#include <netinet/in.h>

namespace Red {

Cabecera::Cabecera()
	: idMensaje()
	, longitud(0)
{
}

Cabecera::Cabecera(TipoMensaje idMensaje, uint32_t longitud)
	: idMensaje(idMensaje)
	, longitud(longitud)
{
}

Cabecera::Cabecera (std::vector<uint8_t> base)
	: idMensaje()
	, longitud()
{
	idMensaje = (TipoMensaje)base[0];
	longitud = ntohl(*(uint32_t*)(&base[1]));
}

std::vector<uint8_t> Cabecera::aVector() const {
	std::vector<uint8_t> retval;

	retval.resize(sizeof(idMensaje) + sizeof(longitud));
	retval[0] = (uint8_t)idMensaje;
	*(uint32_t*)(&retval[1]) = htonl(longitud);

	return retval;
}

size_t Cabecera::tamVector () {
	return sizeof(idMensaje) + sizeof(longitud);
}

} /* namespace Red */
