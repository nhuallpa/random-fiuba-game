/*
 * Queso.h
 *
 *  Created on: Nov 29, 2013
 *      Author: lucia
 */

#ifndef QUESO_H_
#define QUESO_H_
#include "../Cuerpo.h"
#include "Domino.h"

namespace simulador {
class Queso: public simulador::Domino {
public:
	Queso(b2World* mundo, Modelo::EntidadWrapper entidad);
	virtual ~Queso();
};
}

#endif /* QUESO_H_ */
