/*
 * Vela.h
 *
 *  Created on: 14/11/2013
 *      Author: stephanie
 */

#ifndef VELA_H_
#define VELA_H_

#include "Simulador/Cuerpo.h"

namespace simulador {

class Vela: public simulador::Cuerpo {
public:
	Vela(b2World* mundo, Modelo::EntidadWrapper entidad);
	virtual ~Vela();
	void vivir();

private:
	b2Body* crearCuerpo();
	void modelarContacto();
};

} /* namespace simulador */
#endif /* VELA_H_ */
