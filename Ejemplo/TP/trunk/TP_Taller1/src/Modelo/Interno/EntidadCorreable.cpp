/*
 * EntidadCorreable.cpp
 *
 *  Created on: Oct 13, 2013
 *      Author: rick
 */

#include "EntidadCorreable.h"

namespace Modelo {

EntidadCorreable::EntidadCorreable()
	: Modelo::Entidad()
{
}


EntidadCorreable::EntidadCorreable(TipoJugador jugador, Modelo::TipoElemento clase, Vec2 centro, Vec2 tamanio, float angulo, bool estadoNormal, unsigned int id)
	: Modelo::Entidad(jugador, clase, centro, tamanio, angulo, estadoNormal, id)
{
}


EntidadCorreable::~EntidadCorreable() {
}


std::vector<Vec2> EntidadCorreable::puntoLigaduraLocal() const {
	std::vector<Vec2> lista;
	lista.emplace_back(0, 0);	// punto central de la figura
	return lista;
}


} /* namespace Modelo */
