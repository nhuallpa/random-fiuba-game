/*
 * Arandela.h
 *
 *  Created on: Nov 2, 2013
 *      Author: rick
 */

#ifndef ARANDELA_H_
#define ARANDELA_H_

#include "EntidadSogeable.h"

namespace Modelo {


class Gancho: public Modelo::EntidadSogeable {

public:
	Gancho();
	Gancho (TipoJugador jugador, Modelo::TipoElemento clase, Vec2 centro = Vec2(0, 0),
			Vec2 tamanio = Vec2(0, 0), float angulo = 0.0f, bool estadoNormal = true, unsigned int id = 0);
	virtual ~Gancho();

	virtual std::vector<Vec2> puntoLigaduraLocal() const;
};


} /* namespace Modelo */

#endif /* ARANDELA_H_ */
