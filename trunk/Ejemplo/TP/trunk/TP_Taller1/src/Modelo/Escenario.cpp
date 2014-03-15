/*
 * Escenario.cpp
 *
 *  Created on: 25/09/2013
 *  Last Amended: 25/09/2013
 *      Author: natuchis
 */

#include "Escenario.h"

#include "Modelo/Mundo.h"
#include "Log/Suceso.h"
#include <string>


Escenario::Escenario()
	: pathFondo("imagenes/fondos/wallpaperMountains.png")
	, mundo()
{
}


Escenario::Escenario(std::string path, Modelo::Mundo mundo)
	: pathFondo(path)
	, mundo(mundo)
{
}


Escenario::~Escenario()
{
}


Escenario Escenario::copiaProfunda() {
	return Escenario(pathFondo, mundo.copiaProfunda());
}


Escenario& Escenario::asignacionProfunda (Escenario base) {
	using std::swap;
	swap(pathFondo, base.pathFondo);
	mundo.asignacionProfunda(std::move(base.mundo));
	return *this;
}
