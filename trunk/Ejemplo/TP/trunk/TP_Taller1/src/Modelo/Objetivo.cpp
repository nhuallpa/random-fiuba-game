/*
 * Objetivo.cpp
 *
 *  Created on: Nov 25, 2013
 *      Author: rick
 */

#include "Objetivo.h"
#include "Sonido/Sonido.h"
#include "Log/Suceso.h"

namespace Modelo {


Objetivo::Objetivo()
	: objetivoDelJuego()
	, descripcion()
	, idEntidad(0)
	, unaZona()
	, idEntidades()
	, objetivoCumplido(false)
	, zonaEscenario(0,0,20,20)
	, idInvalido(false)
{
}


Objetivo::Objetivo(TipoObjetivo unObjetivo, size_t unaEntidad, Rect unaZona,
		std::list<size_t> muchasEntidades, Rect zonaEscenario, std::string desc)
	: objetivoDelJuego(unObjetivo)
	, descripcion(desc)
	, idEntidad(unaEntidad)
	, unaZona(unaZona)
	, idEntidades(muchasEntidades)
	, objetivoCumplido(false)
	, zonaEscenario(zonaEscenario)
	, idInvalido(false)
{
}


Objetivo::~Objetivo() {
}


void Objetivo::checkearElObjetivo(Modelo::Mundo *mundo) {

	if (!idInvalido) {
		Modelo::EntidadWrapper unaEntidad = mundo->buscarElemento(idEntidad);
		if (!unaEntidad.valido() ) {
			Log::Suceso(Log::ERROR, "Se le paso a Objetivo un id de una Entidad que no existe en el Mundo.");
			idInvalido = true;
			return;
		}
		Vec2 tamanioEntidad = unaEntidad.tamanio() - unaEntidad.tamanio() * PORCENTAJE_DE_COLISION/100;
		Rect supEntidad = Rect::deCentro(unaEntidad.centro(), tamanioEntidad);

		switch (objetivoDelJuego) {

		case TipoObjetivo::sacarAlgo:
			if ( !supEntidad.colisiona(unaEntidad.angulo(), unaZona, 0) ) {
				objetivoCumplido = true;
			}
			break;

		case TipoObjetivo::meterAlgo:
			if ( supEntidad.colisiona(unaEntidad.angulo(), unaZona, 0) ) {
				objetivoCumplido = true;
			}
			break;

		case TipoObjetivo::romperGlobo:
		case TipoObjetivo::romperHuevo:
			if (unaEntidad.estadoNormal() == false) {
				objetivoCumplido = true;
			}
			break;
		}
	}
}


bool Objetivo::objetivoEstaCumplido() {
	return objetivoCumplido;
}


} /* namespace Modelo */
