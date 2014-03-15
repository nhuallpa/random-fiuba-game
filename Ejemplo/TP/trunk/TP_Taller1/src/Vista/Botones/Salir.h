/*
 * Salir.h
 *
 *  Created on: 14/09/2013
 *  Last Amended: 15/09/2013
 *      Author: natuchis
 */

#ifndef SALIR_H_
#define SALIR_H_

#include "Vista/Boton.h"

class Salir: public Boton {
public:
	Salir(const FuentePosicion& fuente, Dibujable *destino);
	virtual ~Salir();
};

#endif /* SALIR_H_ */
