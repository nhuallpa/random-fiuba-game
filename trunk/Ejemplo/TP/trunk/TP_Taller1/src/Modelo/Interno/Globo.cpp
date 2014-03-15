/*
 * Globo.cpp
 *
 *  Created on: Oct 13, 2013
 *      Author: rick
 */

#include "Globo.h"

namespace Modelo {

Globo::Globo()
	: Modelo::EntidadSogeable()
{
}


Globo::Globo(TipoJugador jugador, Modelo::TipoElemento clase, Vec2 centro, Vec2 tamanio, float angulo, bool estadoNormal, unsigned int id)
	: Modelo::EntidadSogeable(jugador, clase, centro, tamanio, angulo, estadoNormal, id)
{
}


Globo::~Globo() {
}


std::vector<Vec2> Globo::puntoLigaduraLocal() const {
	std::vector<Vec2> lista;
	lista.emplace_back(0, -0.4 * tamanio.y); // punto central inferior
	return lista;
}


} /* namespace Modelo */
