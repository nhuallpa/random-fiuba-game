/*
 * Polea.h
 *
 *  Created on: Nov 2, 2013
 *      Author: lucia
 */

#ifndef POLEA_H_
#define POLEA_H_
#include "Simulador/Cuerpo.h"
#include <Box2D/Box2D.h>
#include "../Constantes.h"
#include "../JointMaker.h"
#include "Soga.h"

namespace simulador {

//Polea se modela con un objeto redondo del cual cuelgan dos cuerpos.
class Polea : public Cuerpo {
public:
	Polea(b2World* mundo, Modelo::EntidadWrapper entidad);
	Polea (const Polea&) = delete;
	Polea operator= (const Polea&) = delete;
	virtual ~Polea();
	void conectar();
	void vivir();
	std::list<Modelo::EntidadWrapper> getAparejo();
	void romperAparejo();
	b2Vec2 getReactionForce(Cuerpo* afectado);
	Modelo::EntidadWrapper soga1;
	Modelo::EntidadWrapper soga2;
	bool estaCorrupta() const;
private:
	void borrarPulley();
	//TODO: Mover a jointMaker y renombrar como SimuladorHelper... algun día
	Cuerpo* buscarCuerpoEnMundo(Modelo::EntidadWrapper entidad);
	b2Joint* getPulleyJoint();
	b2Body* crearSoporte(b2Body* cuerpo);
	std::pair<Modelo::EntidadWrapper, Modelo::EntidadWrapper> buscarSogasFinales();
	std::pair<Cuerpo*, Cuerpo*> buscarCuerposFinales();
	//SOLO LLAMAR CON UNA SOGA FINAL DE APAREJO.
	Modelo::EntidadWrapper getEntidadSogueada(Modelo::EntidadWrapper soga);
	b2Joint* pJoint;
	bool desatada;
	bool corrupta;
	b2Body* crearCuerpo(b2World* mundo);

};

} /* namespace simulador */
#endif /* POLEA_H_ */
