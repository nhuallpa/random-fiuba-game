/*
 * Canasto.cpp
 *
 *  Created on: 02/12/2013
 *      Author: stephanie
 */

#include "Canasto.h"
#include "Box2D/Box2D.h"
#include "Simulador/Constantes.h"

namespace simulador {

Canasto::Canasto(b2World* mundo, Modelo::EntidadWrapper entidad) {
	this->m_mundo = mundo;
	this->entidad = entidad;
	this->cuerpo = crearCuerpo();
	this->cuerpo->SetUserData(this);
}

Canasto::~Canasto() {
}

b2Body* Canasto::crearCuerpo(){

	Vec2 tamanio = entidad.tamanio()/2;
	Vec2 posicion = entidad.centro();
	//base
	b2EdgeShape base;
	base.Set(b2Vec2(-0.3*tamanio.x,tamanio.y), b2Vec2(0.3*tamanio.x, tamanio.y));

	b2PolygonShape diagonalIzq;
	diagonalIzq.SetAsBox(0, tamanio.y, b2Vec2(-0.7*tamanio.x,0),-15*Constantes::Instancia()->DEGTORAD);

	b2PolygonShape diagonalDer;
	diagonalDer.SetAsBox(0, tamanio.y, b2Vec2(0.7*tamanio.x,0),15*Constantes::Instancia()->DEGTORAD);

	b2BodyDef bodyDef;
	bodyDef.position.Set(posicion.x, posicion.y);

	b2Body* body = m_mundo->CreateBody(&bodyDef);
	body->CreateFixture(&base, 2.0f);
	body->CreateFixture(&diagonalIzq, 2.0f);
	body->CreateFixture(&diagonalDer, 2.0f);

	return body;
}

} /* namespace simulador */
