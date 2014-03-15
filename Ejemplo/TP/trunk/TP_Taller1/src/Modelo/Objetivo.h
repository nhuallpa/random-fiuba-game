/*
 * Objetivo.h
 *
 *  Created on: Nov 25, 2013
 *      Author: rick
 */

#ifndef OBJETIVO_H_
#define OBJETIVO_H_
#include "Modelo/Mundo.h"
#include "Modelo/TipoObjetivo.h"
#include "Utils/Rect.h"
#include <list>
#include <string>

#ifndef PORCENTAJE_DE_COLISION
#define PORCENTAJE_DE_COLISION 80
#endif

namespace Modelo {


class Objetivo {

class Mundo;
class EntidadWrapper;

public:
	Objetivo();
	Objetivo(TipoObjetivo unObjetivo, size_t idEntidad, Rect unaZona,
			std::list<size_t> idEntidades = std::list<size_t>(),
			Rect zonaEscenario = Rect(0,0,20,20), std::string desc = "");
	virtual ~Objetivo();

	void checkearElObjetivo(Modelo::Mundo *mundo);	// metodo que checkea el estado del objetivo
	bool objetivoEstaCumplido();					// getter de 'objetivoCumplido'

// Atributos "privados"
	TipoObjetivo objetivoDelJuego;
	std::string descripcion;

	size_t idEntidad;
	Rect unaZona;
	std::list<size_t> idEntidades;

private:
	bool objetivoCumplido;
	Rect zonaEscenario;

	bool idInvalido;

};


} /* namespace Modelo */

#endif /* OBJETIVO_H_ */
