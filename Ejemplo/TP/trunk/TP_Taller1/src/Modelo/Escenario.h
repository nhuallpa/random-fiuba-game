/*
 * Escenario.h
 *
 *  Created on: 25/09/2013
 *  Last Amended: 25/09/2013
 *      Author: natuchis
 */

#ifndef ESCENARIO_H_
#define ESCENARIO_H_

#include "Modelo/Mundo.h"
#include "Modelo/Objetivo.h"
#include <string>


struct Escenario {

	std::string pathFondo;
	Modelo::Mundo mundo;

	Escenario();
	Escenario(std::string path, Modelo::Mundo mundo);
	~Escenario();

	Escenario copiaProfunda();
	Escenario& asignacionProfunda(Escenario);

};


#endif /* ESCENARIO_H_ */
