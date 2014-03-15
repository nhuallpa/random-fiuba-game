/*
 * Domino.h
 *
 *  Created on: 07/11/2013
 *      Author: stephanie
 */

#ifndef DOMINO_H_
#define DOMINO_H_

#include "Simulador/Cuerpo.h"

namespace simulador {

class Domino: public simulador::Cuerpo {
public:
	Domino(b2World* mundo, Modelo::EntidadWrapper entidad);
	virtual ~Domino();
	void vivir();

private:
	b2Body* crearCuerpo();
	float anguloInicial;
};

} /* namespace simulador */
#endif /* DOMINO_H_ */
