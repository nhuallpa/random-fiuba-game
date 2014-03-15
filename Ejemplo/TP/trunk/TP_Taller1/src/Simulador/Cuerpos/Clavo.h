/*
 * Clavo.h
 *
 *  Created on: 01/11/2013
 *      Author: stephanie
 */

#ifndef CLAVO_H_
#define CLAVO_H_

#include "Simulador/Cuerpo.h"

namespace simulador {

class Clavo: public simulador::Cuerpo {
public:
	Clavo(b2World* mundo, Modelo::EntidadWrapper entidad);
	virtual ~Clavo();

private:
	float anguloInicial;
	b2Body* crearCuerpo();
};

} /* namespace simulador */
#endif /* CLAVO_H_ */
