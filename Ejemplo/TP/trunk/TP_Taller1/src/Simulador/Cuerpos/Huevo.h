/*
 * Huevo.h
 *
 *  Created on: 03/11/2013
 *      Author: stephanie
 */

#ifndef HUEVO_H_
#define HUEVO_H_

#include "Simulador/Cuerpo.h"
#include "Box2D/Box2D.h"

namespace simulador {

class Huevo: public simulador::Cuerpo {
public:
	Huevo(b2World* mundo, Modelo::EntidadWrapper entidad);
	virtual ~Huevo();
	void vivir();
	void destruir();
	void modelarContacto(b2Contact* contact);

private:
	b2Body* crearCuerpo();
	bool seRompio;
	float anguloInicial;
};

} /* namespace simulador */
#endif /* HUEVO_H_ */
