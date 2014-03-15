/*
 * Carrito.h
 *
 *  Created on: Nov 29, 2013
 *      Author: rick
 */

#ifndef CARRITO_H_
#define CARRITO_H_

#include "EntidadSogeable.h"

namespace Modelo {


class Carrito: public Modelo::EntidadSogeable {

public:
	Carrito();
	Carrito (TipoJugador jugador, Modelo::TipoElemento clase, Vec2 centro = Vec2(0, 0),
			Vec2 tamanio = Vec2(0, 0), float angulo = 0.0f, bool estadoNormal = true, unsigned int id = 0);
	virtual ~Carrito();

	virtual std::vector<Vec2> puntoLigaduraLocal() const;

};


} /* namespace Modelo */

#endif /* CARRITO_H_ */
