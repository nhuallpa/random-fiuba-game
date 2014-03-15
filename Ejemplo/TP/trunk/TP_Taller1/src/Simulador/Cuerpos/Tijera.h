/*
 * Tijera.h
 *
 *  Created on: 01/11/2013
 *      Author: stephanie
 */

#ifndef TIJERA_H_
#define TIJERA_H_

#include "Simulador/Cuerpo.h"
#include "Simulador/Cuerpos/Soga.h"
#include "Simulador/Cuerpos/Polea.h"

namespace simulador {

enum class MangoAtado : size_t {
	mango_derecho,
	mango_izquierdo,
	mango_arriba,
	mango_abajo,
};

class Tijera: public simulador::Cuerpo {


public:
	Tijera(b2World* mundo, Modelo::EntidadWrapper entidad);
	Tijera (const Tijera&) = delete;
	Tijera& operator= (const Tijera&) = delete;
	virtual ~Tijera();
	void vivir();
	Modelo::EntidadWrapper soga1;
	Modelo::EntidadWrapper soga2;

private:
	b2Body* crearCuerpo();
	void modelarContacto();
	b2Body* cerrarTijera();
	void cambiarForma();
	void modelarContactoCuerpoTijera();
	/* Esto es para el cuerpo que se crea entre medio de la tijera cerrada.
	 * Esta hecho asi porque de otra manera se arruinaba el modelado del la
	 * tijera cerrda.
	 */
	void modelarContactoCuerpoCortante();
	void controlarTension();
	void controlarTensionDosSogas();
	void destruirCuerpoCortante();

	int cantidadDeVecesCerrado;
	b2Body* cuerpoCortante;
	b2Body* soporte;
	b2RevoluteJoint* joint;
	int delay;
	Cuerpo* buscarCuerpoEnMundo(Modelo::EntidadWrapper entidad);
	void cambiarACuerpoTijeraConSensor();
	b2Body* cuerpoDeCostado; //para q no se pise la tijera cuando esta rotado
							 //al ser dinamico

	MangoAtado mapMangoSoga(Modelo::EntidadWrapper);
	b2Vec2 getReactionForce(Modelo::EntidadWrapper soga);
	bool estaTirando(std::pair<Modelo::EntidadWrapper, MangoAtado> soga, b2Vec2 fuerza);

};

} /* namespace simulador */
#endif /* TIJERA_H_ */
