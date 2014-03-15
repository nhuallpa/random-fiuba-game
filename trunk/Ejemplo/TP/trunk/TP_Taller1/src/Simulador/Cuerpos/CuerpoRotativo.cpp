/*
 * CuerpoRotativo.cpp
 *
 *  Created on: 08/10/2013
 *      Author: stephanie
 */

#include "CuerpoRotativo.h"

#include "Simulador/JointMaker.h"
#include <Box2D/Box2D.h>

namespace simulador {

CuerpoRotativo::CuerpoRotativo(b2Vec2 posInicial,
		b2World* mundo, float angulo, float radio, bool sentidoHorario,
		bool sentidoAntihorario, bool isMotor, Modelo::EntidadWrapper entidad)
	: rJoint(nullptr)
	, posicion(posInicial)
	, angulo(angulo)
	, radio(radio)
	, soporte(nullptr)
	, sentidoAntihorario(sentidoAntihorario)
	, sentidoHorario(sentidoHorario)
{
	this->posicionInicial = posInicial;
	this->cuerpo = crearCuerpo(mundo);
	this->soporte = crearSoporte(mundo);
	this->entidad = entidad;
	this->m_mundo = mundo;
	float motorSpeed = Constantes::Instancia()->motorSpeed;
	float maxTorque = Constantes::Instancia()->maxMotorTorque;
	if (sentidoAntihorario){
		this->rJoint = JointMaker::crearRevoluteJoint(mundo,this->soporte, this->cuerpo,
				isMotor, (-1)*motorSpeed, maxTorque);
	}else{
		this->rJoint = JointMaker::crearRevoluteJoint(mundo,this->soporte, this->cuerpo,
				isMotor, motorSpeed, maxTorque);
	}

}

CuerpoRotativo::~CuerpoRotativo() {
	m_mundo->DestroyBody(soporte);
	m_mundo->DestroyBody(cuerpo);
}

b2RevoluteJoint* CuerpoRotativo::getJoint() {
	return rJoint;
}

b2Body* CuerpoRotativo::getSoporte(){
	return soporte;
}

b2Body* CuerpoRotativo::crearCuerpo(b2World* mundo){
	b2Body* body;
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(this->posicion.x, this->posicion.y);
	b2FixtureDef fixtureDef;
	fixtureDef.density = Constantes::Instancia()->densidadCuerpoRotativo;
	b2CircleShape circleShape;
	circleShape.m_radius = radio;
	fixtureDef.shape = &circleShape;
	body = mundo->CreateBody( &bodyDef );
	body->CreateFixture( &fixtureDef );
	return body;
}

b2Body* CuerpoRotativo::crearSoporte(b2World* mundo){
	b2Body* body;
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(cuerpo->GetPosition().x, cuerpo->GetPosition().y);
	b2FixtureDef fixtureDef;
	b2CircleShape circleShape;
	circleShape.m_radius = Constantes::Instancia()->radioSoporte;
	fixtureDef.shape = &circleShape;
	body = mundo->CreateBody( &bodyDef );
	body->CreateFixture( &fixtureDef );
	return body;
}

void CuerpoRotativo::setRadio(float){
	return;
}

void CuerpoRotativo::setSentidoAntihorario(bool sentido){
	this->sentidoAntihorario = sentido;
}

bool CuerpoRotativo::getSentidoAntihorario(){
	return this->sentidoAntihorario;
}

void CuerpoRotativo::setSentidoHorario(bool sentido){
	this->sentidoHorario = sentido;
}

bool CuerpoRotativo::getSentidoHorario(){
	return this->sentidoHorario;
}

float CuerpoRotativo::getRadio(){
	return radio;
}

void CuerpoRotativo::setSentidoSegunCuerpoRotativo(CuerpoRotativo* cuerpoRotativo){
	if (cuerpoRotativo->getSentidoHorario()){
		sentidoHorario = false;
		sentidoAntihorario = true;
	}else{
		sentidoHorario = true;
		sentidoAntihorario = false;
	}
}
} /* namespace simulador */
