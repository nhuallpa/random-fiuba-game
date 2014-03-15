/*
 * FlechaDown.h
 *
 *  Created on: 16/09/2013
 *  Last Amended: 16/09/2013
 *      Author: natuchis
 */

#ifndef FLECHADOWN_H_
#define FLECHADOWN_H_

#include "Vista/Boton.h"

class ToolBar;

class FlechaDown: public Boton {
public:
	FlechaDown(const FuentePosicion& fuente, Dibujable *destino, ToolBar* toolbar);
	virtual ~FlechaDown();
};

#endif /* FLECHADOWN_H_ */
