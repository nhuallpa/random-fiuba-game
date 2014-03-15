/*
 * PelotaBasquet.h
 *
 *  Created on: Oct 4, 2013
 *      Author: lucia
 */

#ifndef PELOTABASQUET_H_
#define PELOTABASQUET_H_
#include "Pelota.h"
namespace simulador {

class PelotaBasquet:public Pelota {
public:
	PelotaBasquet(b2World* mundo, Modelo::EntidadWrapper entidad);
	virtual ~PelotaBasquet();
};

} /* namespace simulador */
#endif /* PELOTABASQUET_H_ */
