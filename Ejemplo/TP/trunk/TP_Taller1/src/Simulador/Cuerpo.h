/*
 * Cuerpo.h
 *
 *  Created on: Oct 4, 2013
 *      Author: lucia
 */

#ifndef CUERPO_H_
#define CUERPO_H_

#include "Modelo/EntidadWrapper.h"
#include "Utils/Vec2.h"

class b2Body;
class b2RevoluteJoint;
class b2Vec2;
class b2World;

namespace simulador {

class Engranaje;

/*
 * Interfaz que representa a un cuerpo existente en el
 * espacio físico de la simulación.
 * */
class Cuerpo {
public:
	Cuerpo();
	Cuerpo(Modelo::EntidadWrapper entidad, b2Body *cuerpo, Vec2 posicionInicial, b2World *m_mundo);

	Cuerpo (const Cuerpo&) = delete;
	Cuerpo& operator= (const Cuerpo&) = delete;
	virtual ~Cuerpo();

	virtual b2Body* getCuerpo(){ return cuerpo; };
	virtual void tocarse(Cuerpo* otroCuerpo, b2World* mundo);
	virtual void conectarA(simulador::Engranaje* eng, b2World* mundo);
	//Lo necesito para la correa.
	virtual b2RevoluteJoint* getJoint(){return NULL;};
	virtual b2Body* getSoporte(){return NULL;};
	//vivir va a actualizar lo que deba actualizar de las entities,
	//y aplicar las fuerzas, torques e impulsos necesarios por cada
	//STEP del simulador
	virtual void vivir(){};
	virtual void destruir();

	virtual void modelarContacto();

	Modelo::EntidadWrapper entidad;
	b2Body* cuerpo;
	Vec2 posicionInicial;
	b2World* m_mundo;
};

} /* namespace simulador */
#endif /* CUERPO_H_ */
