/*
 * Polea.cpp
 *
 *  Created on: Nov 2, 2013
 *      Author: rick
 */

#include "Polea.h"

namespace Modelo {

Polea::Polea()
	: Modelo::EntidadSogeable()
{
}


Polea::Polea(TipoJugador jugador, Modelo::TipoElemento clase, Vec2 centro, Vec2 tamanio, float angulo, bool estadoNormal, unsigned int id)
	: Modelo::EntidadSogeable(jugador, clase, centro, tamanio, angulo, estadoNormal, id)
{
}


Polea::~Polea() {
}


std::vector<Vec2> Polea::puntoLigaduraLocal() const {
	std::vector<Vec2> lista;

	Vec2 offset = Vec2(0.45, 0) * tamanio.x;
	lista.emplace_back(offset);		// puntos extremos izquierda y derecha, centrales en y
	lista.emplace_back(-offset);	// notar que esto es en el estado inicial, sino depende del angulo de giro

	return lista;
}


} /* namespace Modelo */
