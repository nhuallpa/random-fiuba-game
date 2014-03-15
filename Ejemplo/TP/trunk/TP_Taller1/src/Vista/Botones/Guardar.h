/*
 * Guardar.h
 *
 *  Created on: 14/09/2013
 *  Last Amended: 15/09/2013
 *      Author: natuchis
 */

#ifndef GUARDAR_H_
#define GUARDAR_H_

#include "Vista/Boton.h"

namespace Modelo {
	class Juego;
}

using namespace std;

class Guardar: public Boton {
public:
	Guardar(const FuentePosicion& fuente, Dibujable *destino, Modelo::Juego* escenario, std::string pathArch);
	virtual ~Guardar();
};

#endif /* GUARDAR_H_ */
