/*
 * Motor.h
 *
 *  Created on: 04/10/2013
 *      Author: stephanie
 */

#ifndef MOTOR_H_
#define MOTOR_H_

#include "Simulador/Cuerpos/CuerpoRotativo.h"

namespace simulador {

class Motor: public CuerpoRotativo {
public:
	Motor(b2World* mundo, Modelo::EntidadWrapper entidad);
	virtual ~Motor();

};

} /* namespace simulador */
#endif /* MOTOR_H_ */
