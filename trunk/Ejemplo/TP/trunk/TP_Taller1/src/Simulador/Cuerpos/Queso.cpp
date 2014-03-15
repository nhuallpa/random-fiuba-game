/*
 * Queso.cpp
 *
 *  Created on: Nov 29, 2013
 *      Author: lucia
 */

#include "Queso.h"

namespace simulador {
Queso::Queso(b2World* mundo, Modelo::EntidadWrapper entidad)
	: Domino(mundo, entidad)
{
}

Queso::~Queso() {
}
}
