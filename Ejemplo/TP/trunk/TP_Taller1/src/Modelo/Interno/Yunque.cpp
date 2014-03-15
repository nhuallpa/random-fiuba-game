/*
 * Yunque.cpp
 *
 *  Created on: Nov 2, 2013
 *      Author: rick
 */

#include "Yunque.h"

namespace Modelo {

Yunque::Yunque()
	: Modelo::EntidadSogeable()
{
}


Yunque::Yunque(TipoJugador jugador, Modelo::TipoElemento clase, Vec2 centro, Vec2 tamanio, float angulo, bool estadoNormal, unsigned int id)
	: Modelo::EntidadSogeable(jugador, clase, centro, tamanio, angulo, estadoNormal, id)
{
}


Yunque::~Yunque() {
}


std::vector<Vec2> Yunque::puntoLigaduraLocal() const {
	std::vector<Vec2> lista;
//	Vec2 offsetIzq = Vec2(-0.47, 0) * tamanio.x + Vec2(0, 0.4) * tamanio.y;
//	Vec2 offsetDer = Vec2( 0.47, 0) * tamanio.x + Vec2(0, 0.4) * tamanio.y;
//
//	if (sentidoHorario) {	// sentidoHorario == true   ==>  izquierda (caso inicial)
//		lista.emplace_back(offsetIzq);
//	}
//	else {					// sentidoHorario == false  ==>  derecha
//		lista.emplace_back(offsetDer);
//	}						// puntos extremos izquierda ó derecha, segun corresponda, de la parte superior de la figura

	lista.emplace_back(0, 0);	// punto central de la figura
	return lista;
}


} /* namespace Modelo */
