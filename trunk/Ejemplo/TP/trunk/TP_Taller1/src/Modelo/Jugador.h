/*
 * Jugador.h
 *
 *  Created on: Nov 2, 2013
 *      Author: rick
 */

#ifndef JUGADOR_H_
#define JUGADOR_H_

#include "Controlador/Mouse.h"
#include "Modelo/TipoJugador.h"
#include "Modelo/TipoElemento.h"
#include "Modo/ModoUsuario.h"
#include "Utils/Rect.h"
#include "Vista/FuentesPosicion/FuenteMouse.h"
#include <map>

namespace Modelo {

class Jugador {

public:
	Jugador();
	Jugador(Modelo::TipoJugador tipoJugador);
	Jugador(Modelo::TipoJugador tipoJugador, std::map<Modelo::TipoElemento, size_t> entidadesDisponibles, Rect regionDeEdicion);

	Jugador (const Jugador&) = default;
	Jugador& operator= (const Jugador&) = default;
	~Jugador();

// Atributos
	Modelo::TipoJugador tipoJugador;
	Modo::EstadoJuego modoJuegoActual;
	std::map<Modelo::TipoElemento, size_t> entidadesDisponibles;
	Rect regionDeEdicion;

	controlador::Mouse::Estado estadoMouse;
	Modelo::TipoElemento elementoMouse;
	FuenteMouse *fuenteMouse;
	Vec2 posicionMouse;
	Rect canvasAbsoluto;
};


} /* namespace Modelo */

#endif /* JUGADOR_H_ */
