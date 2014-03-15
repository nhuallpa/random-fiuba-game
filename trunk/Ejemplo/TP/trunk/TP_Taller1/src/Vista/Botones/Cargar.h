/*
 * Cargar.h
 *
 *  Created on: 14/09/2013
 *  Last Amended: 24/09/2013
 *      Author: natuchis, rick
 */

#ifndef CARGAR_H_
#define CARGAR_H_

#include "Vista/Boton.h"

class Textbox;

class Cargar: public Boton {

public:
	Cargar (const FuentePosicion& fuente, Dibujable* destino, Textbox* textbox);
	virtual ~Cargar();
};

#endif /* CARGAR_H_ */

