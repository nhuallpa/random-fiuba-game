/*
 * Codo.h
 *
 *  Created on: 03/11/2013
 *      Author: stephanie
 */

#ifndef CODO_H_
#define CODO_H_

#include "Simulador/Cuerpo.h"

namespace simulador {

class Codo: public simulador::Cuerpo {
public:
	Codo(b2World* mundo, Modelo::EntidadWrapper entidad);
	virtual ~Codo();

private:
	b2Body* crearCuerpo();
};

} /* namespace simulador */
#endif /* CODO_H_ */
