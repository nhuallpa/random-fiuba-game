/*
 * TipoJugador.cpp
 *
 *  Created on: Nov 2, 2013
 *      Author: rick
 */

#include "TipoJugador.h"
#include "Log/Suceso.h"

#include <list>
#include <utility>

namespace Modelo {


std::list<TipoJugador> listaTipoJugador = {
	TipoJugador::Jugador1,
	TipoJugador::Jugador2,
	TipoJugador::Jugador3,
	TipoJugador::Jugador4,
	TipoJugador::Escenario
};


/* static en variable global := solo visible desde esta unidad de compilacion */
static std::list<std::pair<TipoJugador, std::string>> valores = {
	make_pair(TipoJugador::Jugador1, std::string("Jugador1")),
	make_pair(TipoJugador::Jugador2, std::string("Jugador2")),
	make_pair(TipoJugador::Jugador3, std::string("Jugador3")),
	make_pair(TipoJugador::Jugador4, std::string("Jugador4")),
	make_pair(TipoJugador::Escenario, std::string("Escenario"))
};


std::string tipoJugadorToString(TipoJugador jugador) {
	for (auto par : valores) {
		if (par.first == jugador) {
			return par.second;
		}
	}
	throw Log::Suceso(Log::DEBUG, "Se intento convertir jugador desconocido a string.");
}


TipoJugador stringToTipoJugador(std::string nombreJugador) {
	for (auto par : valores) {
		if (par.second == nombreJugador) {
			return par.first;
		}
	}
	std::string mensaje = std::string("Se intento convertir el string desconocido ")
		+ "'" + nombreJugador + "'" + " a jugador.";
	throw Log::Suceso(Log::ERROR, mensaje);
}


} /* namespace Modelo */
