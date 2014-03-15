/*
 * Objetivo.h
 *
 *  Created on: Dec 1, 2013
 *      Author: lucia
 */

#ifndef OBJETIVO_SERIALIZACION_H_
#define OBJETIVO_SERIALIZACION_H_

#include "Serializacion/Interno/convertir.h"
#include "Modelo/Objetivo.h"
namespace Serializacion {

template <>
struct convertir<Modelo::Objetivo>
{
	static Objeto serializar (Modelo::Objetivo obj);
	static Modelo::Objetivo deserializar (const Objeto& objeto);
	static Modelo::Objetivo aplicarCambios (const Objeto& objeto, Modelo::Objetivo base);
};

} /* namespace Serializacion */
#endif /* OBJETIVO_SERIALIZACION_H_ */
