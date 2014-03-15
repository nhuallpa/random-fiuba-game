/*
 * Jugador.cpp
 *
 *  Created on: Nov 2, 2013
 *      Author: rick
 */

#include "Jugador.h"

#include "Log/Logger.h"
#include "Log/Suceso.h"

namespace Modelo {

Jugador::Jugador()
	: tipoJugador(Modelo::TipoJugador::Escenario)
	, modoJuegoActual(Modo::EstadoJuego::edicion)
	, entidadesDisponibles()
	, regionDeEdicion()
	, estadoMouse(controlador::Mouse::Estado::inicial)
	, elementoMouse()
	, fuenteMouse()
	, posicionMouse()
	, canvasAbsoluto()
{
}

Jugador::Jugador(Modelo::TipoJugador tipoJugador)
	: tipoJugador(tipoJugador)
	, modoJuegoActual(Modo::EstadoJuego::edicion)
	, entidadesDisponibles()
	, regionDeEdicion()
	, estadoMouse(controlador::Mouse::Estado::inicial)
	, elementoMouse()
	, fuenteMouse()
	, posicionMouse()
	, canvasAbsoluto()
{
	if (tipoJugador != Modelo::TipoJugador::Escenario) {
		Log::Suceso(Log::DEBUG, "Se deberia usarse el otro constructor para los jugadores.");
	}
}

Jugador::Jugador(Modelo::TipoJugador tipoJugador, std::map<Modelo::TipoElemento, size_t> entidadesDisponibles, Rect regionDeEdicion)
	: tipoJugador(tipoJugador)
	, modoJuegoActual(Modo::EstadoJuego::edicion)
	, entidadesDisponibles(entidadesDisponibles)
	, regionDeEdicion(regionDeEdicion)
	, estadoMouse(controlador::Mouse::Estado::inicial)
	, elementoMouse()
	, fuenteMouse()
	, posicionMouse()
	, canvasAbsoluto()
{
	if (tipoJugador == Modelo::TipoJugador::Escenario) {
		Log::Suceso(Log::DEBUG, "Se recomienda usar el otro constructor para 'Escenario'.");
	}
}


Jugador::~Jugador() {
}


} /* namespace Modelo */
