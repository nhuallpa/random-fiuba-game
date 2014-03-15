/*
 * Correa.cpp
 *
 *  Created on: Oct 9, 2013
 *      Author: lucia
 */

#include "Correa.h"

namespace simulador {

Correa::Correa(b2World* mundo, Cuerpo* ca, Cuerpo* cb, float ratio, Modelo::EntidadWrapper entidad)
	: junturaEngranaje(nullptr)
{
	this->entidad = entidad;
	b2Body* soporte1 = ca->getSoporte();
	b2Body* soporte2 = cb->getSoporte();
	b2Joint* rJoint1 = ca->getJoint();
	b2Joint* rJoint2 = cb->getJoint();
	junturaEngranaje = JointMaker::crearGearJoint(mundo, soporte1,soporte2,rJoint1,rJoint2,ratio);
}

Correa::~Correa() {
}

} /* namespace simulador */
