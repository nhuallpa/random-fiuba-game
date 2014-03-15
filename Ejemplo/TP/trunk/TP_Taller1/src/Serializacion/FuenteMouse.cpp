/*
 * FuenteMouse.cpp
 *
 *  Created on: 01/12/2013
 *  Last Amended: 01/12/2013
 *      Author: natuchis
 */

#include "FuenteMouse.h"

#include "Serializacion/Rect.h"
#include "Serializacion/Interno/Mapa.h"

namespace Serializacion {

Objeto convertir<FuenteMouse*>::serializar (FuenteMouse* obj) {
	Mapa retval;
	retval["superficieBase"] = obj->superficieBase;
	retval["angulo"] = obj->angulo;
	retval["estadoNormal"] = obj->estadoNormal;
	return retval;
}

FuenteMouse* convertir<FuenteMouse*>::deserializar (const Objeto& objeto) {
	return aplicarCambios(objeto, new FuenteMouse());
}

FuenteMouse* convertir<FuenteMouse*>::aplicarCambios (const Objeto& objeto, FuenteMouse* base) {
	FuenteMouse* retval = base;
	Mapa mapa = objeto.getMapa();
	mapa.asignar_si(retval->superficieBase, "superficieBase");
	mapa.asignar_si(retval->angulo, "angulo");
	mapa.asignar_si(retval->estadoNormal, "estadoNormal");
	return retval;
}

} /* namespace Serializacion */
