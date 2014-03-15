/*
 * EntidadSogeable.cpp
 *
 *  Created on: Oct 13, 2013
 *      Author: rick
 */

#include "EntidadSogeable.h"

namespace Modelo {

EntidadSogeable::EntidadSogeable()
	: Modelo::Entidad()
{
}


EntidadSogeable::EntidadSogeable(TipoJugador jugador, Modelo::TipoElemento clase, Vec2 centro, Vec2 tamanio, float angulo, bool estadoNormal, unsigned int id)
	: Modelo::Entidad(jugador, clase, centro, tamanio, angulo, estadoNormal, id)
{
}


EntidadSogeable::~EntidadSogeable() {
}


bool EntidadSogeable::tieneUnElemPuenteAtado() const {
	if (!this->elemPuenteAtado.empty()) {
		return true;
	}
	return false;
}


} /* namespace Modelo */
