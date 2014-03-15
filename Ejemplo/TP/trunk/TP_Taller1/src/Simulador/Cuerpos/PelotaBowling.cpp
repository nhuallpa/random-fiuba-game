/*
 * PelotaBowling.cpp
 *
 *  Created on: Oct 4, 2013
 *      Author: lucia
 */

#include "PelotaBowling.h"

#include "Simulador/Constantes.h"
#include <Box2D/Box2D.h>

namespace simulador {

PelotaBowling::PelotaBowling(b2World* mundo, Modelo::EntidadWrapper entidad):
	Pelota(Constantes::Instancia()->coeficienteRestitucionPelotaBowling,
	       Constantes::Instancia()->densidadPelotaBowling, mundo, entidad)
{
	//cambio el userData
	this->cuerpo->SetUserData(this);
}

PelotaBowling::~PelotaBowling() {
}

} /* namespace simulador */
