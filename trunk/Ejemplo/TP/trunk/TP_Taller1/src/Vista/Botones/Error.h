/*
 * Error.h
 *
 *  Created on: 04/12/2013
 *  Last Amended: 04/12/2013
 *      Author: natuchis
 */

#ifndef ERROR_H_
#define ERROR_H_

#include "Vista/Boton.h"

#include <string>

class Error: public Boton {

public:
	Error(const FuentePosicion& unaFuente, Dibujable* unDestino, std::string mensaje);
	virtual ~Error();
};

#endif /* ERROR_H_ */
