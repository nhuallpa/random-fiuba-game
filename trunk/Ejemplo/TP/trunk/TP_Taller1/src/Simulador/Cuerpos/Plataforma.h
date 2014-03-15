/*
 * Plataforma.h
 *
 *  Created on: Oct 3, 2013
 *      Author: lucia
 */

#ifndef PLATAFORMA_H_
#define PLATAFORMA_H_

#include "Simulador/Cuerpo.h"

namespace simulador {

class Plataforma : public Cuerpo {
public:
	Plataforma(b2World* mundo, Modelo::EntidadWrapper entidad);
	virtual ~Plataforma();
private:
	b2Body* crearCuerpo(b2World* mundo);
	Vec2 dimensiones;
	float angulo;
};

} /* namespace simulador */
#endif /* PLATAFORMA_H_ */
