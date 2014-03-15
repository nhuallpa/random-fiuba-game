/*
 * Canio.cpp
 *
 *  Created on: 03/11/2013
 *      Author: stephanie
 */

#include "Canio.h"
#include "Simulador/Constantes.h"
#include "Box2D/Box2D.h"

namespace simulador {

Canio::Canio(b2World* mundo, Modelo::EntidadWrapper entidad){
	this->posicionInicial = entidad.centro();
	this->m_mundo = mundo;
	this->entidad = entidad;
	this->cuerpo = crearCuerpo();
	this->cuerpo->SetUserData(this);
}

Canio::~Canio() {
	m_mundo->DestroyBody(cuerpo);
}

b2Body* Canio::crearCuerpo(){
	float32 hx = entidad.tamanio().x/2;
	float32 hy = entidad.tamanio().y/2;

	b2PolygonShape polygonShape1;
	//hx-0.3f
	polygonShape1.SetAsBox(hx, 0.0f, b2Vec2(0.0f, 3*hy/4), 0);
	b2FixtureDef fixtureDef1;
	fixtureDef1.shape = &polygonShape1;

	//hx-0.3f
	b2PolygonShape polygonShape2;
	polygonShape2.SetAsBox(hx, 0.0f, b2Vec2(0.0f, -3*hy/4), 0);
	b2FixtureDef fixtureDef2;
	fixtureDef2.shape = &polygonShape2;

	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.angle = entidad.angulo() * Constantes::Instancia()->DEGTORAD;
	bodyDef.position.Set(entidad.centro().x, entidad.centro().y);

	b2Body* body = m_mundo->CreateBody(&bodyDef);
	body->CreateFixture(&fixtureDef1);
	body->CreateFixture(&fixtureDef2);

	return body;
}
} /* namespace simulador */
