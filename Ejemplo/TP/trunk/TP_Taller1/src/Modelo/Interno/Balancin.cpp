/*
 * Balancin.cpp
 *
 *  Created on: Oct 13, 2013
 *      Author: rick
 */

#include "Balancin.h"

namespace Modelo {

Balancin::Balancin()
	: Modelo::EntidadSogeable()
{
}


Balancin::Balancin(TipoJugador jugador, Modelo::TipoElemento clase, Vec2 centro, Vec2 tamanio, float angulo, bool estadoNormal, unsigned int id)
	: Modelo::EntidadSogeable(jugador, clase, centro, tamanio, angulo, estadoNormal, id)
{
}


Balancin::~Balancin() {
}


std::vector<Vec2> Balancin::puntoLigaduraLocal() const {
	std::vector<Vec2> lista;

	Vec2 offset = Vec2(0.45, 0) * tamanio.x;
	lista.emplace_back(offset);		// puntos extremos izquierda y derecha, centrales en y
	lista.emplace_back(-offset);

	return lista;
}


} /* namespace Modelo */
