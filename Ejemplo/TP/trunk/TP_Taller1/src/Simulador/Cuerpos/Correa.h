/*
 * Correa.h
 *
 *  Created on: Oct 9, 2013
 *      Author: lucia
 */

#ifndef CORREA_H_
#define CORREA_H_
#include <Box2D/Box2D.h>
#include "Simulador/JointMaker.h"
#include "Simulador/Cuerpo.h"
#include "CuerpoRotativo.h"

namespace simulador {

class Correa: public simulador::Cuerpo {
public:
	Correa(b2World* mundo, Cuerpo* ca, Cuerpo* cb,
			float ratio, Modelo::EntidadWrapper entidad);
	Correa (const Correa&) = delete;
	Correa& operator= (const Correa&) = delete;
	virtual ~Correa();
private:
	b2GearJoint* junturaEngranaje;
};

} /* namespace simulador */
#endif /* CORREA_H_ */
