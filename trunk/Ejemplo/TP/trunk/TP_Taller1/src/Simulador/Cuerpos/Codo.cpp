/*
 * Codo.cpp
 *
 *  Created on: 03/11/2013
 *      Author: stephanie
 */

#include "Codo.h"
#include "Simulador/Constantes.h"
#include "Box2D/Box2D.h"

namespace simulador {

Codo::Codo(b2World* mundo, Modelo::EntidadWrapper entidad) {
	this->m_mundo = mundo;
	this->entidad = entidad;
	this->posicionInicial = entidad.centro();
	this->cuerpo = crearCuerpo();
	this->cuerpo->SetUserData(this);
}

Codo::~Codo() {
	m_mundo->DestroyBody(cuerpo);
}

b2Body* Codo::crearCuerpo(){
	Vec2 tamanio = entidad.tamanio()/2;
	Vec2 posicion = entidad.centro();

	b2BodyDef bodyDef;
	bodyDef.position.Set(posicion.x, posicion.y);
	bodyDef.angle = entidad.angulo() * Constantes::Instancia()->DEGTORAD;
	bodyDef.type = b2_staticBody;

	//creo edge shape
	//lado vertical izquierdo
	b2EdgeShape edge1;
	edge1.Set(b2Vec2(-tamanio.x + tamanio.x/8, -tamanio.y), b2Vec2(-tamanio.x + tamanio.x/8, tamanio.y/4));

	//lado horizontal inferior
	b2EdgeShape edge2;
	edge2.Set(b2Vec2(-tamanio.x/4, tamanio.y - tamanio.y/8), b2Vec2(tamanio.x, tamanio.y - tamanio.y/8));

	//lado vertical derecho
	b2EdgeShape edge3;
	edge3.Set(b2Vec2(tamanio.x/8, -tamanio.y), b2Vec2(tamanio.x/8, -tamanio.y/5)); //el desde 0.0, algo, si quiero modelar solo las lineas del medio

	//lado horizontal superior.
	b2EdgeShape edge4;
	edge4.Set(b2Vec2(tamanio.x/4, 0.0f), b2Vec2(tamanio.x, 0.0f));

	//diagonal que une lado vertical derecho y lado horizontal superior
	b2EdgeShape edge5;
	edge5.Set(b2Vec2(tamanio.x/8, -tamanio.y/5), b2Vec2(tamanio.x/4, 0.0f));

	//diagonal que une lado vertical izquierdo y lado horizontal inferior
	b2EdgeShape edge6;
	edge6.Set(b2Vec2(-0.8*tamanio.x, tamanio.y/4), b2Vec2(-tamanio.x/4, tamanio.y));

	b2Body* body = m_mundo->CreateBody(&bodyDef);
	body->CreateFixture(&edge1, 0.0f);
	body->CreateFixture(&edge2, 0.0f);
	body->CreateFixture(&edge3, 0.0f);
	body->CreateFixture(&edge4, 0.0f);
	body->CreateFixture(&edge5, 0.0f);
	body->CreateFixture(&edge6, 0.0f);

	return body;
}
} /* namespace simulador */
