/*
 * MotorRaton.h
 *
 *  Created on: Nov 28, 2013
 *      Author: lucia
 */

#ifndef MOTORRATON_H_
#define MOTORRATON_H_

#include "Motor.h"
#include "RayCastQueso.h"

namespace simulador {

class MotorRaton : public Motor {
public:
	MotorRaton(b2World* mundo, Modelo::EntidadWrapper entidad);
	void vivir();
	virtual ~MotorRaton();
private:
	b2Body* getCuerpo(b2Vec2 punto);
	int sentido;
};

}

#endif /* MOTORRATON_H_ */
