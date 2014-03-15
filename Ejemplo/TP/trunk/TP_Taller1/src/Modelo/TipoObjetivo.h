/*
 * TipoObjetivo.h
 *
 *  Created on: Nov 25, 2013
 *      Author: rick
 */

#ifndef TIPOOBJETIVO_H_
#define TIPOOBJETIVO_H_

#include <string>
#include <list>

namespace Modelo {


enum class TipoObjetivo : size_t
{
	sacarAlgo,		// pelota, globo, huevo, yunque, etc
	meterAlgo,		// pelota, globo, huevo, yunque, etc
	romperGlobo,
	romperHuevo,
};

extern std::list<TipoObjetivo> listaTipoObjetivo;

std::string tipoObjetivoToString (TipoObjetivo unObjetivo);
TipoObjetivo stringToTipoObjetivo (std::string unObjetivo);


} /* namespace Modelo */

#endif /* TIPOOBJETIVO_H_ */
