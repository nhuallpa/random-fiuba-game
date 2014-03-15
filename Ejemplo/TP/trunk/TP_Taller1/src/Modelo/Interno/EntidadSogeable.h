/*
 * EntidadSogeable.h
 *
 *  Created on: Oct 13, 2013
 *      Author: rick
 */

#ifndef ENTIDADSOGEABLE_H_
#define ENTIDADSOGEABLE_H_

#include "Entidad.h"

namespace Modelo {


class EntidadSogeable: public Modelo::Entidad {

public:
	EntidadSogeable();
	EntidadSogeable (TipoJugador jugador, Modelo::TipoElemento clase, Vec2 centro = Vec2(0, 0),
			Vec2 tamanio = Vec2(0, 0), float angulo = 0.0f, bool estadoNormal = true, unsigned int id = 0);
	virtual ~EntidadSogeable();

	virtual bool tieneUnElemPuenteAtado() const;

};

} /* namespace Modelo */

#endif /* ENTIDADSOGEABLE_H_ */
