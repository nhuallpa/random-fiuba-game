/*
 * Arandela.cpp
 *
 *  Created on: Nov 2, 2013
 *      Author: rick
 */

#include "Gancho.h"

namespace Modelo {


Gancho::Gancho()
	: Modelo::EntidadSogeable()
{
}


Gancho::Gancho(TipoJugador jugador, Modelo::TipoElemento clase, Vec2 centro, Vec2 tamanio, float angulo, bool estadoNormal, unsigned int id)
	: Modelo::EntidadSogeable(jugador, clase, centro, tamanio, angulo, estadoNormal, id)
{
}


Gancho::~Gancho() {
}


std::vector<Vec2> Gancho::puntoLigaduraLocal() const {
	std::vector<Vec2> lista;
	lista.emplace_back(0, 0);	// punto central de la figura
	return lista;
}


} /* namespace Modelo */
