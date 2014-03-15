/*
 * TipoObjetivo.cpp
 *
 *  Created on: Nov 25, 2013
 *      Author: rick
 */

#include "TipoObjetivo.h"
#include "Log/Suceso.h"

#include <list>
#include <utility>

namespace Modelo {


std::list<TipoObjetivo> listaTipoObjetivo = {
	TipoObjetivo::sacarAlgo,
	TipoObjetivo::meterAlgo,
	TipoObjetivo::romperGlobo,
	TipoObjetivo::romperHuevo,
};


static std::list<std::pair<TipoObjetivo, std::string>> valores = {
	make_pair(TipoObjetivo::sacarAlgo, std::string("sacarAlgo")),
	make_pair(TipoObjetivo::meterAlgo, std::string("meterAlgo")),
	make_pair(TipoObjetivo::romperGlobo, std::string("romperGlobo")),
	make_pair(TipoObjetivo::romperHuevo, std::string("romperHuevo")),
};


std::string tipoObjetivoToString(TipoObjetivo unObjetivo) {
	for (auto par : valores) {
		if (par.first == unObjetivo) {
			return par.second;
		}
	}
	throw Log::Suceso(Log::DEBUG, "Se intento convertir un objetivo desconocido a string.");
}


TipoObjetivo stringToTipoObjetivo(std::string unObjetivo) {
	for (auto par : valores) {
		if (par.second == unObjetivo) {
			return par.first;
		}
	}
	std::string mensaje = std::string("Se intento convertir el objetivo desconocido ")
		+ "'" + unObjetivo + "'" + " a un tipo objetivo.";
	throw Log::Suceso(Log::ERROR, mensaje);
}


} /* namespace Modelo */
