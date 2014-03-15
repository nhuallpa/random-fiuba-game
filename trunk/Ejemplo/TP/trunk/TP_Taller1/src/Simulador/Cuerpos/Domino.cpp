/*
 * Domino.cpp
 *
 *  Created on: 07/11/2013
 *      Author: stephanie
 */

#include "Domino.h"
#include "Box2D/Box2D.h"
#include "Simulador/Constantes.h"

namespace simulador {

Domino::Domino(b2World* mundo, Modelo::EntidadWrapper entidad)
	: anguloInicial(entidad.angulo())
{
	this->m_mundo = mundo;
	this->entidad = entidad;
	this->posicionInicial = entidad.centro();
	this->cuerpo = crearCuerpo();
	this->cuerpo->SetUserData(this);
}

Domino::~Domino() {
	m_mundo->DestroyBody(cuerpo);
}

b2Body* Domino::crearCuerpo(){
	b2BodyDef myBodyDef;
	myBodyDef.type = b2_dynamicBody;
	myBodyDef.position.Set(posicionInicial.x, posicionInicial.y);
	myBodyDef.angle = entidad.angulo() * Constantes::Instancia()->DEGTORAD;

	b2PolygonShape boxShape;
	boxShape.SetAsBox(entidad.tamanio().x/2, entidad.tamanio().y/2);

	b2FixtureDef boxFixtureDef;
	boxFixtureDef.shape = &boxShape;
	boxFixtureDef.density = 15.0f;
	boxFixtureDef.friction = 0.1f;

	b2Body* body = m_mundo->CreateBody(&myBodyDef);
	body->CreateFixture(&boxFixtureDef);

	return body;
}
void Domino::vivir(){
	entidad.angulo() = cuerpo->GetAngle() * Constantes::Instancia()->RADTODEG;
	entidad.centro() = Vec2(cuerpo->GetPosition());
}

} /* namespace simulador */
