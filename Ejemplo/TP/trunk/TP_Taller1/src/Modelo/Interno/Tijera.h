/*
 * Tijera.h
 *
 *  Created on: Nov 2, 2013
 *      Author: rick
 */

#ifndef TIJERA_H_
#define TIJERA_H_

#include "EntidadSogeable.h"

namespace Modelo {


class Tijera: public Modelo::EntidadSogeable {

public:
	Tijera();
	Tijera (TipoJugador jugador, Modelo::TipoElemento clase, Vec2 centro = Vec2(0, 0),
			Vec2 tamanio = Vec2(0, 0), float angulo = 0.0f, bool estadoNormal = true, unsigned int id = 0);
	virtual ~Tijera();

	virtual std::vector<Vec2> puntoLigaduraLocal() const;

};


} /* namespace Modelo */

#endif /* TIJERA_H_ */
