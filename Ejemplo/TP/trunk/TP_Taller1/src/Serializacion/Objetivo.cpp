/*
 * Objetivo.cpp
 *
 *  Created on: Dec 1, 2013
 *      Author: lucia
 */

#include "Objetivo.h"

#include "Serializacion/Rect.h"
#include "Serializacion/Vec2.h"
#include "Serializacion/Interno/Mapa.h"
#include "Serializacion/Interno/Vector.h"
#include "Modelo/TipoElemento.h"

namespace Serializacion {

Objeto convertir<Modelo::Objetivo>::serializar (Modelo::Objetivo obj) {
	Mapa retval;
	retval["objetivoDelJuego"] = Modelo::tipoObjetivoToString(obj.objetivoDelJuego);
	retval["idEntidad"] = obj.idEntidad;
	retval["unaZona"] = obj.unaZona;
	Vector idEntidadesObjetivo;
	for (size_t id : obj.idEntidades) {
		idEntidadesObjetivo.push_back(id);
	}
	retval["idEntidades"] = idEntidadesObjetivo;
	retval["descripcion"] = obj.descripcion;
	return retval;
}

Modelo::Objetivo convertir<Modelo::Objetivo>::deserializar (const Objeto& objeto) {
	return aplicarCambios(objeto, Modelo::Objetivo());
}

Modelo::Objetivo convertir<Modelo::Objetivo>::aplicarCambios (const Objeto& objeto, Modelo::Objetivo base) {
	Modelo::Objetivo retval = base;
	Mapa mapa = objeto.getMapa();

	retval.objetivoDelJuego = Modelo::stringToTipoObjetivo(mapa["objetivoDelJuego"]);

	Vector vectorEntidades = mapa["idEntidades"].getVector();
	for (size_t id : vectorEntidades.valores) {
		retval.idEntidades.push_back(id);
	}
	mapa.asignar_si(retval.unaZona, "unaZona");
	mapa.asignar_si(retval.idEntidad, "idEntidad");
	mapa.asignar_si(retval.descripcion, "descripcion");


	return retval;
}

} /* namespace Serializacion */
