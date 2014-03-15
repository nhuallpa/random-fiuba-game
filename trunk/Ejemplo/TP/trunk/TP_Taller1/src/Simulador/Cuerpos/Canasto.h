/*
 * Canasto.h
 *
 *  Created on: 02/12/2013
 *      Author: stephanie
 */

#ifndef CANASTO_H_
#define CANASTO_H_

#include "Simulador/Cuerpo.h"

namespace simulador {

class Canasto: public simulador::Cuerpo {
public:
	Canasto(b2World* mundo, Modelo::EntidadWrapper entidad);
	virtual ~Canasto();
private:
	b2Body* crearCuerpo();
};

} /* namespace simulador */
#endif /* CANASTO_H_ */
