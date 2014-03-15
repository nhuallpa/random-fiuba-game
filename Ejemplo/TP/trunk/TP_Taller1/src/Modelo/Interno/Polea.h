/*
 * Polea.h
 *
 *  Created on: Nov 2, 2013
 *      Author: rick
 */

#ifndef POLEA_H_
#define POLEA_H_

#include "EntidadSogeable.h"

namespace Modelo {


class Polea: public Modelo::EntidadSogeable {

public:
	Polea();
	Polea (TipoJugador jugador, Modelo::TipoElemento clase, Vec2 centro = Vec2(0, 0),
			Vec2 tamanio = Vec2(0, 0), float angulo = 0.0f, bool estadoNormal = true, unsigned int id = 0);
	virtual ~Polea();

	virtual std::vector<Vec2> puntoLigaduraLocal() const;

};


} /* namespace Modelo */

#endif /* POLEA_H_ */
