/*
 * EntidadNoMovilElementoPuente.h
 *
 *  Created on: Oct 12, 2013
 *      Author: rick
 */

#ifndef ENTIDADNOMOVILELEMENTOPUENTE_H_
#define ENTIDADNOMOVILELEMENTOPUENTE_H_

#include "Entidad.h"

namespace Modelo {


class EntidadElementoPuente: public Modelo::Entidad {

public:
	EntidadElementoPuente();
	EntidadElementoPuente (TipoJugador jugador, Modelo::TipoElemento clase, Vec2 centro = Vec2(0, 0),
			Vec2 tamanio = Vec2(0, 0), float angulo = 0.0f, bool estadoNormal = true, unsigned int id = 0);
	virtual ~EntidadElementoPuente();

	// Soga y correa no colisionan con otros objetos
	virtual bool colicionaCon(Entidad* otraEntidad) const;
};


} /* namespace Modelo */

#endif /* ENTIDADNOMOVILELEMENTOPUENTE_H_ */
