/*
 * Yunque.cpp
 *
 *  Created on: 01/11/2013
 *      Author: stephanie
 */

#include "Yunque.h"
#include <Box2D/Box2D.h>
#include "Simulador/Constantes.h"

namespace simulador {

Yunque::Yunque(b2World* mundo, Modelo::EntidadWrapper entidad)
	: anguloInicial(entidad.angulo())
{
	this->m_mundo = mundo;
	this->entidad = entidad;
	this->cuerpo = crearCuerpo();
	this->cuerpo->SetUserData(this);
	this->posicionInicial = entidad.centro();
}

Yunque::~Yunque() {
	m_mundo->DestroyBody(cuerpo);
}

b2Body* Yunque::crearCuerpo(){

	Vec2 tamanio = entidad.tamanio()/2;
	float32 hx = entidad.tamanio().x/2;
	float32 hy = entidad.tamanio().y/2;

	//rectangulo central
	b2PolygonShape polygon1;
	polygon1.SetAsBox(hx/4, hy/2, b2Vec2(0.0f, -0.4*hy), 0);

	//la base
	b2PolygonShape polygon2;
	polygon2.SetAsBox(hx/2, hy/4, b2Vec2(0.0f, hy - hy/3), 0);

	//edge para los triangulos
	//triangulo superior izquierdo
	b2EdgeShape edge1;
	edge1.Set(b2Vec2(-tamanio.x, -0.9*tamanio.y), b2Vec2(-0.4*tamanio.x, -0.9*tamanio.y));
	b2EdgeShape edge2;
	edge2.Set(b2Vec2(-tamanio.x, -0.8*tamanio.y), b2Vec2(-0.4*tamanio.x, -0.2*tamanio.y));

	//triangulo superior derecho
	b2EdgeShape edge3;
	edge3.Set(b2Vec2(0.4*tamanio.x, -0.8*tamanio.y), b2Vec2(tamanio.x, -0.8*tamanio.y));
    b2EdgeShape edge4;
    edge4.Set(b2Vec2(0.4*tamanio.x, -0.2*tamanio.y), b2Vec2(tamanio.x, -0.7*tamanio.y));

	b2BodyDef bd;
	bd.type = b2_dynamicBody;
	bd.position.Set(entidad.centro().x, entidad.centro().y);
	bd.angle = entidad.angulo() * Constantes::Instancia()->DEGTORAD;

	b2Body* body = m_mundo->CreateBody(&bd);
	body->CreateFixture(&edge1, Constantes::Instancia()->densidadYunque);
	body->CreateFixture(&edge2, Constantes::Instancia()->densidadYunque);
	body->CreateFixture(&edge3, Constantes::Instancia()->densidadYunque);
	body->CreateFixture(&edge4, Constantes::Instancia()->densidadYunque);
    body->CreateFixture(&polygon1, Constantes::Instancia()->densidadYunque);
    body->CreateFixture(&polygon2, Constantes::Instancia()->densidadYunque);
	return body;
}

void Yunque::vivir(){
	modelarContacto();
	entidad.angulo() = cuerpo->GetAngle() * Constantes::Instancia()->RADTODEG;
	entidad.centro() = Vec2(cuerpo->GetPosition());
}

void Yunque::modelarContacto(){

	for (b2ContactEdge* ce = cuerpo->GetContactList(); ce; ce = ce->next){
		b2Contact* c = ce->contact;
		c->SetRestitution(0.0f);
	};

}
} /* namespace simulador */
