/*
 * Yunque.h
 *
 *  Created on: 01/11/2013
 *      Author: stephanie
 */

#ifndef YUNQUE_H_
#define YUNQUE_H_

#include "Simulador/Cuerpo.h"

namespace simulador {

class Yunque: public simulador::Cuerpo {
public:
	Yunque(b2World* mundo, Modelo::EntidadWrapper entidad);
	virtual ~Yunque();
	void vivir();
	void modelarContacto();

private:
	b2Body* crearCuerpo();
	float anguloInicial;
};

} /* namespace simulador */
#endif /* YUNQUE_H_ */
