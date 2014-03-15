/*
 * PelotaBasquet.cpp
 *
 *  Created on: Oct 4, 2013
 *      Author: lucia
 */

#include "PelotaBasquet.h"

#include "Simulador/Constantes.h"
#include <Box2D/Box2D.h>

namespace simulador {

PelotaBasquet::PelotaBasquet(b2World* mundo, Modelo::EntidadWrapper entidad)
	: Pelota(Constantes::Instancia()->coeficienteRestitucionPelotaBasquet,
                 Constantes::Instancia()->densidadPelotaBasquet, mundo, entidad)
{
	//cambio el userData
	this->cuerpo->SetUserData(this);
}

PelotaBasquet::~PelotaBasquet() {
}

} /* namespace simulador */
