/*
 * Carrito.cpp
 *
 *  Created on: Nov 29, 2013
 *      Author: rick
 */

#include "Carrito.h"

namespace Modelo {

Carrito::Carrito()
	: Modelo::EntidadSogeable()
{
}


Carrito::Carrito(TipoJugador jugador, Modelo::TipoElemento clase, Vec2 centro, Vec2 tamanio, float angulo, bool estadoNormal, unsigned int id)
	: Modelo::EntidadSogeable(jugador, clase, centro, tamanio, angulo, estadoNormal, id)
{
}


Carrito::~Carrito() {
}


std::vector<Vec2> Carrito::puntoLigaduraLocal() const {
	std::vector<Vec2> lista;

//	if (estadoNormal) {		// punto superior izquierdo (caso initial)
//		Vec2 offset = Vec2( 0.45, 0) * tamanio.x + Vec2(0, 0.45) * tamanio.y;
//		lista.emplace_back(offset);
//	}
//	else {					// punto superior derecho
//		Vec2 offset = Vec2(-0.45, 0) * tamanio.x + Vec2(0, 0.45) * tamanio.y;
//		lista.emplace_back(offset);
//	}

	Vec2 offset = Vec2( 0.01, 0) * tamanio.x + Vec2(0, 0.1) * tamanio.y;
	lista.emplace_back(offset);

	return lista;
}

} /* namespace Modelo */
