/*
 * FuenteMouse.h
 *
 *  Created on: 01/12/2013
 *  Last Amended: 01/12/2013
 *      Author: natuchis
 */

#ifndef SERIALIZACION_FUENTEMOUSE_H_
#define SERIALIZACION_FUENTEMOUSE_H_

#include "Serializacion/Interno/convertir.h"
#include "Vista/FuentesPosicion/FuenteMouse.h"

namespace Serializacion {

template <>
struct convertir<FuenteMouse*>
{
	static Objeto serializar (FuenteMouse* obj);
	static FuenteMouse* deserializar (const Objeto& objeto);
	static FuenteMouse* aplicarCambios (const Objeto& objeto, FuenteMouse* base);
};

} /* namespace Serializacion */
#endif /* SERIALIZACION_FUENTEMOUSE_H_ */
