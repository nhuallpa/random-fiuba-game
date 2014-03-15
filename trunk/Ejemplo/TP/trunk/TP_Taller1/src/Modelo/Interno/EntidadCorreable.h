/*
 * EntidadCorreable.h
 *
 *  Created on: Oct 13, 2013
 *      Author: rick
 */

#ifndef ENTIDADCORREABLE_H_
#define ENTIDADCORREABLE_H_

#include "Entidad.h"

namespace Modelo {


class EntidadCorreable: public Modelo::Entidad {

public:
	EntidadCorreable();
	EntidadCorreable (TipoJugador jugador, Modelo::TipoElemento clase, Vec2 centro = Vec2(0, 0),
			Vec2 tamanio = Vec2(0, 0), float angulo = 0.0f, bool estadoNormal = true, unsigned int id = 0);
	virtual ~EntidadCorreable();

	virtual std::vector<Vec2> puntoLigaduraLocal() const;

};


} /* namespace Modelo */

#endif /* ENTIDADCORREABLE_H_ */
