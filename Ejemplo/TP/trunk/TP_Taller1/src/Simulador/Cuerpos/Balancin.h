/*
 * Balancin.h
 *
 *  Created on: Oct 4, 2013
 *      Author: lucia
 */

#ifndef BALANCIN_H_
#define BALANCIN_H_

#include "Simulador/Cuerpo.h"
#include "Utils/Vec2.h"

namespace simulador {

class Balancin: public Cuerpo {
public:
	Balancin(b2World* mundo, Modelo::EntidadWrapper entidad);

	Balancin (const Balancin&) = delete;
	Balancin& operator= (const Balancin&) = delete;
	virtual ~Balancin();

	void vivir();

private:
	b2Body* crearCuerpo(b2World* mundo);
	b2Body* crearSoporte(b2Body* plataforma, b2World* mundo);
	void crearJuntura(b2Body* plataforma, b2Body* soporte, b2World* mundo);
	Vec2 dimensiones;
	b2Body* soporte;
	float anguloInicial;
};

} /* namespace simulador */
#endif /* BALANCIN_H_ */
