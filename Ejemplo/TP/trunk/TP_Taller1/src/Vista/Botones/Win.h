/*
 * Win.h
 *
 *  Created on: 04/12/2013
 *  Last Amended: 04/12/2013
 *      Author: natuchis
 */

#ifndef WIN_H_
#define WIN_H_

#include "Vista/Boton.h"

class Win: public Boton {

public:
	Win(const FuentePosicion& fuente, Dibujable* destino, bool* aviso);
	virtual ~Win();
};

#endif /* WIN_H_ */
