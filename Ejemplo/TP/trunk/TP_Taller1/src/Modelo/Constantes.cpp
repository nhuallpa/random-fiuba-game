/*
 * Constantes.cpp
 *
 *  Created on: Oct 16, 2013
 *      Author: rick
 */

#include "Constantes.h"

namespace Modelo {


Constantes* Constantes::instanciaUnica = NULL;

float Constantes::radioPelotaBasquet = 15;
float Constantes::radioPelotaBowling = 15;

float Constantes::radioGlobo = 15;

float Constantes::radioEngranajeL = 0.7f;
float Constantes::radioEngranajeM = 0.5f;
float Constantes::radioEngranajeS = 0.3f;

float Constantes::radioMotor = 10;


Constantes* Constantes::Instancia() {
	if (instanciaUnica == NULL) {
		instanciaUnica = new Constantes();
	}
	return instanciaUnica;
}


Modelo::Constantes::Constantes() {
}


Modelo::Constantes::Constantes(const Constantes& unaInstancia) {
	(void)unaInstancia;		// unused parameter
}


Constantes& Modelo::Constantes::operator =(const Constantes& otraInstancia) {
	(void)otraInstancia;	// unused parameter
	return *this;
}


Constantes::~Constantes() {
}


} /* namespace Modelo */
