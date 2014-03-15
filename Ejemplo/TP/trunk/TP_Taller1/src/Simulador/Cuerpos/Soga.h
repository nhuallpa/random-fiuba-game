/*
 * Soga.h
 *
 *  Created on: 04/10/2013
 *      Author: stephanie
 */

#ifndef SOGA_H_
#define SOGA_H_

#ifndef TIEMPO_DE_QUEMADO_NECESARIO
#define TIEMPO_DE_QUEMADO_NECESARIO 18
#endif

#include "Simulador/Cuerpo.h"

class b2RopeJoint;

namespace simulador {

class Soga: public simulador::Cuerpo {
public:
	Soga(b2World* mundo, b2Body* bodyA, b2Body* bodyB, Modelo::EntidadWrapper entidad);
	Soga(b2World* mundo, b2Body* bodyA, b2Body* bodyB, Modelo::EntidadWrapper entidad, float maxlength);

	Soga (const Soga&) = delete;
	Soga& operator= (const Soga&) = delete;
	virtual ~Soga();

	void unir(b2World* mundo, b2Vec2 puntoA, b2Vec2 puntoB);
	void unir(b2World* mundo, b2Vec2 puntoA, b2Vec2 puntoB, float maxlength);
	void vivir();
	void modelarContacto();
	void cortarSoga();
	b2RopeJoint* getRopeJoint();

private:
	b2Body* crearCuerpoSoga(b2World* mundo, int incremento);
	b2Body* crearCuerpo();
	void actualizarCuerpo();
	b2Body* bodyA;
	b2Body* bodyB;
	Cuerpo* cuerpoA;
	Cuerpo* cuerpoB;
	b2RopeJoint* rJoint;
	Vec2 puntoLigaduraA;
	Vec2 puntoLigaduraB;
	bool existeSoga;
	size_t tiempoQuemandose;
};

} /* namespace simulador */
#endif /* SOGA_H_ */
