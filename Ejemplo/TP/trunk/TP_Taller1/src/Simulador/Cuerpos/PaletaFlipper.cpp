/*
 * PaletaFlipper.cpp
 *
 *  Created on: Nov 13, 2013
 *      Author: lucia
 */

#include "PaletaFlipper.h"

#include "Sonido/Sonido.h"
#include "../JointMaker.h"
#include <math.h>
#include <iostream>

namespace simulador {

//Estado normal = paleta izquierda
//!Estado normal = paleta derecha
PaletaFlipper::PaletaFlipper(b2World* mundo, Modelo::EntidadWrapper entidad)
	: rJoint(nullptr)
	, sentido(1)
	, contadorLevantarFlipper(0)
{
	this->entidad = entidad;
	entidad.accionar() = false;
	this->m_mundo = mundo;
	sentido = (entidad.estadoNormal()) ? 1 : -1;
	float offset = (sentido)*(entidad.tamanio().x/4);
	b2Body* flipper = crearCuerpo();
	b2Body* soporte = crearSoporte(offset);

	//Anchor del soporte (0)
	b2Vec2 anchorA = b2Vec2(0,0);

	//Anchor de la paleta
	b2Vec2 anchorB = b2Vec2(cuerpo->GetLocalPoint(soporte->GetPosition()));

	if (entidad.estadoNormal()) {
		rJoint = JointMaker::crearRevoluteJoint(m_mundo, soporte, flipper,
				true, 0.0, 100000.0, true, -5.0*Constantes::DEGTORAD,
				entidad.angulo()*Constantes::DEGTORAD, anchorA, anchorB );
	}
	else {
		rJoint = JointMaker::crearRevoluteJoint(m_mundo, soporte, flipper,
				true, 0.0, 100000.0, true,  entidad.angulo()*Constantes::DEGTORAD,
				5.0f*Constantes::DEGTORAD, anchorA, anchorB);
	}
	rJoint->SetMotorSpeed((sentido)*10.0f);
}

b2Body* PaletaFlipper::crearCuerpo() {
	b2Vec2 tam = entidad.tamanio();
	b2BodyDef bd;
	bd.type = b2_dynamicBody;
	bd.position = entidad.centro();
	bd.angle = entidad.angulo()*Constantes::DEGTORAD;
	b2Body* flipper = m_mundo->CreateBody(&bd);
	b2PolygonShape triangulo;
	triangulo.SetAsBox(tam.x/2, tam.y/3);
	b2FixtureDef fd;
	fd.shape = &triangulo;
	fd.density = Constantes::Instancia()->densidadPaletaFlipper;
	flipper->CreateFixture(&fd);
	this->cuerpo = flipper;
	flipper->SetUserData(this);
	return flipper;
}

b2Body* PaletaFlipper::crearSoporte(float offset) {
	b2FixtureDef pin;
	b2CircleShape circulo;
	circulo.m_radius = 0;
	pin.shape=&circulo;
	b2BodyDef soporteDef;
	soporteDef.type = b2_staticBody;
	auto cte = Constantes::Instancia();
	Vec2 pos = Vec2(-offset, 0);
	pos = Vec2(1,-1)*pos.rotar(cuerpo->GetAngle()*cte->DEGTORAD);
	pos = pos+entidad.centro();
	soporteDef.position = b2Vec2(pos.x, pos.y);
	b2Body* soporte = m_mundo->CreateBody(&soporteDef);
	soporte->CreateFixture(&pin);
	return soporte;
}


void PaletaFlipper::vivir() {
	if(entidad.accionar()) {
		if (contadorLevantarFlipper == 0) {
			Sonido::Instancia()->playSound(entidad);
			contadorLevantarFlipper++;
		}
		rJoint->SetMotorSpeed(-(sentido)*20.0f);
	} else {
		rJoint->SetMotorSpeed((sentido)*10.0f);
		contadorLevantarFlipper = 0;
	}
	this->entidad.angulo() = this->cuerpo->GetAngle() * Constantes::RADTODEG;
	this->entidad.centro() = this->cuerpo->GetPosition();
}

PaletaFlipper::~PaletaFlipper() {
}

} /* namespace simulador */
