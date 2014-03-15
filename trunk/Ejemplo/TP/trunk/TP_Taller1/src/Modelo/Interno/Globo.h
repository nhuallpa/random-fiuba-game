/*
 * Globo.h
 *
 *  Created on: Oct 13, 2013
 *      Author: rick
 */

#ifndef GLOBO_H_
#define GLOBO_H_

#include "EntidadSogeable.h"

namespace Modelo {


class Globo: public Modelo::EntidadSogeable {

public:
	Globo();
	Globo (TipoJugador jugador, Modelo::TipoElemento clase, Vec2 centro = Vec2(0, 0),
			Vec2 tamanio = Vec2(0, 0), float angulo = 0.0f,  bool estadoNormal = true, unsigned int id = 0);
	virtual ~Globo();

	virtual std::vector<Vec2> puntoLigaduraLocal() const;

};


} /* namespace Modelo */

#endif /* GLOBO_H_ */
