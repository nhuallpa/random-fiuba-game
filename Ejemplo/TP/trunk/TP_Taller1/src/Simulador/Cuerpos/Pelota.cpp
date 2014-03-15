/*
 * Pelota.cpp
 *
 *  Created on: Oct 3, 2013
 *      Author: lucia
 */

#include "Pelota.h"

#include "Simulador/Constantes.h"
#include <Box2D/Box2D.h>

namespace simulador {

Pelota::Pelota(float coefRestitucion,
               float densidad,
               b2World* mundo,
               Modelo::EntidadWrapper entidad)
	: coeficienteRestitucion(coefRestitucion)
	, densidad(densidad)
	, radio(entidad.radio())
	, anguloInicial(entidad.angulo())
{
	this->posicionInicial = entidad.centro();
	this->cuerpo = crearCuerpo(mundo);
	this->entidad = entidad;
	this->m_mundo = mundo;
}

Pelota::~Pelota() {
	m_mundo->DestroyBody(cuerpo);
}

b2Body* Pelota::crearCuerpo(b2World* mundo) {
	b2BodyDef myBodyDef;
	//Es dinamico porque se ve sujeto a toda la fisica del juego.
	myBodyDef.type = b2_dynamicBody;
	myBodyDef.position.Set(posicionInicial.x, posicionInicial.y);
	b2Body* pelotaCuerpo = mundo->CreateBody(&myBodyDef);

	//Tiene forma de circulo porq es una pelota.
	b2CircleShape circleShape;
	circleShape.m_p.Set(0, 0);
	circleShape.m_radius = this->radio;

	b2FixtureDef myFixtureDef;
	myFixtureDef.shape = &circleShape;
	myFixtureDef.density = this->densidad;
	myFixtureDef.restitution = this->coeficienteRestitucion;

	pelotaCuerpo->CreateFixture(&myFixtureDef);
	pelotaCuerpo->SetLinearDamping(Constantes::Instancia()->dampingAire / pelotaCuerpo->GetMass());
	pelotaCuerpo->SetAngularDamping(Constantes::Instancia()->dampingAire / pelotaCuerpo->GetMass());
	return pelotaCuerpo;

}

void Pelota::vivir() {
	entidad.centro() = Vec2(cuerpo->GetPosition());
	entidad.angulo() = cuerpo->GetAngle()*Constantes::Instancia()->RADTODEG;;
}

} /* namespace simulador */
