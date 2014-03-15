/*
 * Carrito.cpp
 *
 *  Created on: 29/11/2013
 *      Author: stephanie
 */

#include "Carrito.h"
#include "../Constantes.h"
#include "../JointMaker.h"
#include <Box2D/Box2D.h>
#include <math.h>

namespace simulador {

#define VELOCIDAD_MINIMA_PARA_ANIMAR 0.5

Carrito::Carrito(b2World* mundo, Modelo::EntidadWrapper entidad)
	: m_rueda1(nullptr)
	, m_rueda2(nullptr)
{
	this->m_mundo = mundo;
	this->entidad = entidad;

	b2Vec2 tamanio = entidad.tamanio()/2;
	b2Vec2 entidadCentro = entidad.centro();
	float entidadAngulo = entidad.angulo() * Constantes::Instancia()->DEGTORAD;


	float radioRuedas = (tamanio.y * 30/100);
	b2Vec2 tamanioCarro(tamanio.x, tamanio.y-radioRuedas);

	b2Body* carro;

	b2BodyDef bd;
	bd.type = b2_dynamicBody;
	bd.position = b2Vec2(entidadCentro.x, entidadCentro.y);
	bd.angle = entidadAngulo;
	carro = m_mundo->CreateBody(&bd);

	//Creo la base
	b2PolygonShape chasis;
	chasis.SetAsBox(tamanioCarro.x,tamanioCarro.y);
	b2FixtureDef fix;
	fix.shape = &chasis;
	fix.density = 10.0f;
	fix.friction = 5.0f;
	carro->CreateFixture(&fix);


	//Las ruedas
	b2Body* rueda1;
	b2Body* rueda2;


	b2CircleShape circle;
	circle.m_radius = radioRuedas;

	bd.position = b2Vec2(tamanioCarro.x*1/2+carro->GetWorldCenter().x,
				tamanioCarro.y+carro->GetWorldCenter().y);

	b2Vec2 localAnchorA = b2Vec2(tamanioCarro.x*1/2, tamanioCarro.y);

	bd.angle = 0;
	rueda1 = m_mundo->CreateBody(&bd);
	b2FixtureDef fixR;
	fixR.shape = &circle;
	fixR.density = 30.0f;
	rueda1->CreateFixture(&fixR);

	bd.position = b2Vec2(-tamanioCarro.x*1/2+carro->GetWorldCenter().x,
			tamanioCarro.y+carro->GetWorldCenter().y);

	b2Vec2 localAnchorB = b2Vec2(-tamanioCarro.x*1/2, tamanioCarro.y);
	rueda2 = m_mundo->CreateBody(&bd);
	rueda2->CreateFixture(&fixR);

	//Los Joints
	JointMaker::crearRevoluteJoint(m_mundo, rueda1, carro, b2Vec2(0,0), localAnchorA);
	JointMaker::crearRevoluteJoint(m_mundo, rueda2, carro, b2Vec2(0,0), localAnchorB);

	this->m_rueda1 = rueda1;
	this->m_rueda2 = rueda2;
	rueda1->SetUserData(this);
	rueda2->SetUserData(this);
	carro->SetUserData(this);
	this->cuerpo = carro;
}

void Carrito::vivir(){
	//Si el carrito se está moviendo y las ruedas están girando
	Vec2 vel(this->cuerpo->GetLinearVelocity());
	Vec2 velRuedas(this->m_rueda1->GetAngularVelocity());
	if(vel.abs() > VELOCIDAD_MINIMA_PARA_ANIMAR && velRuedas.abs() > VELOCIDAD_MINIMA_PARA_ANIMAR) {
		entidad.accionar() = true;
	} else {
		entidad.accionar() = false;
	}
	this->entidad.centro() = this->cuerpo->GetPosition();
	this->entidad.angulo() = this->cuerpo->GetAngle()*Constantes::Instancia()->RADTODEG;
}

Carrito::~Carrito() {
}

} /* namespace simulador */
