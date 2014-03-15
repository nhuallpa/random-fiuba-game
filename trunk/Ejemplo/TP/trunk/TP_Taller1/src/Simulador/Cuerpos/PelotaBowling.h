/*
 * PelotaBowling.h
 *
 *  Created on: Oct 4, 2013
 *      Author: lucia
 */

#ifndef PELOTABOWLING_H_
#define PELOTABOWLING_H_
#include "Pelota.h"
namespace simulador {

class PelotaBowling:public Pelota {
public:
	PelotaBowling(b2World* mundo, Modelo::EntidadWrapper entidad);
	virtual ~PelotaBowling();
};

} /* namespace simulador */
#endif /* PELOTABOWLING_H_ */
