/*
 * Canio.h
 *
 *  Created on: 03/11/2013
 *      Author: stephanie
 */

#ifndef CANIO_H_
#define CANIO_H_

#include "Simulador/Cuerpo.h"

namespace simulador {

class Canio: public simulador::Cuerpo {
public:
	Canio(b2World* mundo, Modelo::EntidadWrapper entidad);
	virtual ~Canio();

private:
	b2Body* crearCuerpo();
};

} /* namespace simulador */
#endif /* CANIO_H_ */
