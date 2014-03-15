/*
 * Yunque.h
 *
 *  Created on: Nov 2, 2013
 *      Author: rick
 */

#ifndef YUNQUE_H_
#define YUNQUE_H_

#include "EntidadSogeable.h"

namespace Modelo {


class Yunque: public Modelo::EntidadSogeable {

public:
	Yunque();
	Yunque (TipoJugador jugador, Modelo::TipoElemento clase, Vec2 centro = Vec2(0, 0),
			Vec2 tamanio = Vec2(0, 0), float angulo = 0.0f, bool estadoNormal = true, unsigned int id = 0);
	virtual ~Yunque();

	virtual std::vector<Vec2> puntoLigaduraLocal() const;

};


} /* namespace Modelo */

#endif /* YUNQUE_H_ */
