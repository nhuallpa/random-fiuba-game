/*
 * TipoJugador.h
 *
 *  Created on: Nov 2, 2013
 *      Author: rick
 */

#ifndef TIPOJUGADOR_H_
#define TIPOJUGADOR_H_

#include <string>
#include <list>

namespace Modelo {


enum class TipoJugador : size_t
{
	Escenario,
	Jugador1,
	Jugador2,
	Jugador3,
	Jugador4,
};

extern std::list<TipoJugador> listaTipoJugador;

std::string tipoJugadorToString (TipoJugador jugador);
TipoJugador stringToTipoJugador (std::string jugador);


} /* namespace Modelo */

#endif /* TIPOJUGADOR_H_ */
