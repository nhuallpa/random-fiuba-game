/*
 * FlechaUp.h
 *
 *  Created on: 16/09/2013
 *  Last Amended: 16/09/2013
 *      Author: natuchis
 */

#ifndef FLECHAUP_H_
#define FLECHAUP_H_

#include "Vista/Boton.h"

class ToolBar;

class FlechaUp: public Boton {
public:
	FlechaUp(const FuentePosicion& fuente, Dibujable *destino, ToolBar* toolbar);
	virtual ~FlechaUp();
};

#endif /* FLECHAUP_H_ */
