/*
 * Constantes.h
 *
 *  Created on: Oct 16, 2013
 *      Author: rick
 */

#ifndef CONSTANTES_H_
#define CONSTANTES_H_

#include <stddef.h>

namespace Modelo {

// Constantes del modelo, o sea de las entidades
class Constantes {

public:
	static Constantes* Instancia();

	static float radioPelotaBasquet;
	static float radioPelotaBowling;

	static float radioGlobo;

	static float radioEngranajeL;
	static float radioEngranajeM;
	static float radioEngranajeS;

	static float radioMotor;

	virtual ~Constantes();


protected:
	Constantes();
	Constantes(const Constantes& unaInstancia);
	Constantes& operator=(const Constantes& otraInstancia);


private:
	static Constantes* instanciaUnica;

};


} /* namespace Modelo */

#endif /* CONSTANTES_H_ */
