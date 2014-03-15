/*
 * Balancin.h
 *
 *  Created on: Oct 13, 2013
 *      Author: rick
 */

#ifndef BALANCIN_H_
#define BALANCIN_H_

#include "EntidadSogeable.h"

namespace Modelo {


class Balancin: public Modelo::EntidadSogeable {

public:
	Balancin();
	Balancin (TipoJugador jugador, Modelo::TipoElemento clase, Vec2 centro = Vec2(0, 0),
			Vec2 tamanio = Vec2(0, 0), float angulo = 0.0f, bool estadoNormal = true, unsigned int id = 0);
	virtual ~Balancin();

	virtual std::vector<Vec2> puntoLigaduraLocal() const;

};


} /* namespace Modelo */

#endif /* BALANCIN_H_ */
