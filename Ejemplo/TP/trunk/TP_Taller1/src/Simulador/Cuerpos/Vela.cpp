/*
 * Vela.cpp
 *
 *  Created on: 14/11/2013
 *      Author: stephanie
 */

#include "Vela.h"
#include "Simulador/Constantes.h"
#include "Box2D/Box2D.h"

namespace simulador {

Vela::Vela(b2World* mundo, Modelo::EntidadWrapper entidad)
{
	this->m_mundo = mundo;
	this->entidad = entidad;
	this->posicionInicial = entidad.centro();
	this->cuerpo = crearCuerpo();
	this->cuerpo->SetUserData(this);
}

Vela::~Vela() {
	m_mundo->DestroyBody(cuerpo);
}

b2Body* Vela::crearCuerpo(){
	Vec2 posicion = entidad.centro();
	Vec2 tamanio = entidad.tamanio() / 2;

	/* vela */
	b2PolygonShape polygon1;
	polygon1.SetAsBox(0.8*tamanio.x, 0.7*tamanio.y, b2Vec2(0,0.3*tamanio.y), 0);

	b2FixtureDef fixture1;
	fixture1.shape = &polygon1;
	fixture1.density = Constantes::Instancia()->densidadGenerica;

	/* fuego */
	b2PolygonShape polygon2;
	polygon2.SetAsBox(0.1*tamanio.x, 0.2*tamanio.y, b2Vec2(0,-0.8*tamanio.y), 0);

	b2FixtureDef fixture2;
	fixture2.shape = &polygon2;
	fixture2.density = Constantes::Instancia()->densidadGenerica;;
	fixture2.filter.categoryBits = 0x0002;

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(posicion.x, posicion.y);
	bodyDef.angle = entidad.angulo() * Constantes::Instancia()->DEGTORAD;

	b2Body* body = m_mundo->CreateBody(&bodyDef);
	body->CreateFixture(&fixture1);
	body->CreateFixture(&fixture2);

	return body;
}

void Vela::vivir(){
	modelarContacto();
	entidad.angulo() = cuerpo->GetAngle() * Constantes::Instancia()->RADTODEG;
	entidad.centro() = Vec2(cuerpo->GetPosition());
}

void Vela::modelarContacto(){

	for (b2ContactEdge* ce = cuerpo->GetContactList(); ce; ce = ce->next){
		b2Contact* c = ce->contact;
		c->SetRestitution(0.0f);
	};
}
} /* namespace simulador */
