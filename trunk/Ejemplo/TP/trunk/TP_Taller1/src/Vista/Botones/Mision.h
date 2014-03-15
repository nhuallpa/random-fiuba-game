/*
 * Mision.h
 *
 *  Created on: 04/12/2013
 *  Last Amended: 04/12/2013
 *      Author: natuchis
 */

#ifndef MISION_H_
#define MISION_H_

#include "Vista/Boton.h"

class Mision: public Boton {

public:
	Mision(const FuentePosicion& unaFuente, Dibujable* unDestino, std::string mensaje, bool *aviso);
	virtual ~Mision();
};

#endif /* MISION_H_ */
