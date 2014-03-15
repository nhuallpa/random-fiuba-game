/*
 * Gancho.h
 *
 *  Created on: Nov 2, 2013
 *      Author: lucia
 */

#ifndef GANCHO_H_
#define GANCHO_H_

#include "Simulador/Cuerpo.h"
#include <Box2D/Box2D.h>
#include "../Constantes.h"

namespace simulador {

class Gancho : public Cuerpo {
public:
	Gancho(b2World* mundo, Modelo::EntidadWrapper entidad);
	virtual ~Gancho();
	b2Body* crearCuerpo();
};

} /* namespace simulador */
#endif /* GANCHO_H_ */
