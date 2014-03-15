/*
 * TipoElemento.h
 *
 *  Created on: Oct 11, 2013
 *      Author: lucia
 */

#ifndef TIPOELEMENTO_H_
#define TIPOELEMENTO_H_

#include <string>
#include <list>

namespace Modelo {


enum class TipoElemento : size_t {

	// TP2 obligatorios
	PelotaBasquet,
	PelotaBowling,
	Globo,
	Plataforma,
	Balancin,
	Soga,
	Motor,
	Correa,
	Engranaje,
	CintaTransportadora,
	// TP3 obligatorios
	Yunque,
	Gancho,
	Tijera,
	Clavo,
	Polea,
	// TP3 semi-opcionales
	Huevo,
	Canio,
	Codo,
	Carrito,
//	Dinamita,
//	Detonador,
	Domino,
	Vela,
//	Escopeta,
//	Arco,
//	Flecha,
	MotorRaton,
	Queso,
	// TP3 interativos semi-opcionales
//	BombaRemota,
	PaletaFlipper,
//	MotorAdistancia
	//extra
	Canasto,
};

extern std::list<TipoElemento> listaTipoElemento;

std::string tipoElementoToString (TipoElemento clase);
TipoElemento stringToTipoElemento (std::string clase);

bool esMovil (TipoElemento clase);
bool esNoMovil (TipoElemento clase);
bool esElementoPuente (TipoElemento clase);
bool esSogeable (TipoElemento clase);
bool esCorreable (TipoElemento clase);
bool esInteractivo (TipoElemento clase);
bool esAtravesable (TipoElemento clase);


} /* namespace Modelo */

#endif /* TIPOELEMENTO_H_ */
