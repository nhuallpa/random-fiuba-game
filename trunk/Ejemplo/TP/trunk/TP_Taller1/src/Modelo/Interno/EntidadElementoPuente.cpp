/*
 * EntidadNoMovilElementoPuente.cpp
 *
 *  Created on: Oct 12, 2013
 *      Author: rick
 */

#include "EntidadElementoPuente.h"

namespace Modelo {

EntidadElementoPuente::EntidadElementoPuente()
	: Modelo::Entidad()
{
}


EntidadElementoPuente::EntidadElementoPuente(TipoJugador jugador, Modelo::TipoElemento clase, Vec2 centro, Vec2 tamanio, float angulo, bool estadoNormal, unsigned int id)
	: Modelo::Entidad(jugador, clase, centro, tamanio, angulo, estadoNormal, id)
{
}


EntidadElementoPuente::~EntidadElementoPuente() {
}


bool EntidadElementoPuente::colicionaCon(Entidad*) const {
	return false;
}

} /* namespace Modelo */
