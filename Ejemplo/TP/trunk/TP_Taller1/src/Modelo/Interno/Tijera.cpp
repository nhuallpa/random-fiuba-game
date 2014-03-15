/*
 * Tijera.cpp
 *
 *  Created on: Nov 2, 2013
 *      Author: rick
 */

#include "Tijera.h"

namespace Modelo {

Tijera::Tijera()
	: Modelo::EntidadSogeable()
{
}


Tijera::Tijera(TipoJugador jugador, Modelo::TipoElemento clase, Vec2 centro, Vec2 tamanio, float angulo, bool estadoNormal, unsigned int id)
	: Modelo::EntidadSogeable(jugador, clase, centro, tamanio, angulo, estadoNormal, id)
{
}


Tijera::~Tijera() {
}


std::vector<Vec2> Tijera::puntoLigaduraLocal() const {
	std::vector<Vec2> lista;

	if (estadoNormal) {	// tijera abierta (caso inicial)
		Vec2 offsetArr = Vec2(-0.3, 0) * tamanio.x + Vec2(0,  0.3) * tamanio.y;
		Vec2 offsetAba = Vec2(-0.3, 0) * tamanio.x + Vec2(0, -0.3) * tamanio.y;
		lista.emplace_back(offsetArr);
		lista.emplace_back(offsetAba);
	}
	else {					// tijera cerrada
		Vec2 offsetArr = Vec2(-0.35, 0) * tamanio.x + Vec2(0,  0.1) * tamanio.y;
		Vec2 offsetAba = Vec2(-0.35, 0) * tamanio.x + Vec2(0, -0.1) * tamanio.y;
		lista.emplace_back(offsetArr);
		lista.emplace_back(offsetAba);
	}

	return lista;
}


} /* namespace Modelo */
