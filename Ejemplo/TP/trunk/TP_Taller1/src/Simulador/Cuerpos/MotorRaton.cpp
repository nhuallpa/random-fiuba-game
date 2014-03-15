/*
 * MotorRaton.cpp
 *
 *  Created on: Nov 28, 2013
 *      Author: lucia
 */

#include "MotorRaton.h"

#include "Simulador/JointMaker.h"
#include "Box2D/Box2D.h"
#include "../Constantes.h"
#include "Sonido/Sonido.h"


namespace simulador {

MotorRaton::MotorRaton(b2World* mundo, Modelo::EntidadWrapper entidad)
	: Motor(mundo, entidad)
	, sentido(1)
{
	// Cambio el userData
	this->rJoint->SetMotorSpeed(0);

	sentido = (entidad.estadoNormal()) ? 1 : -1;

}

void MotorRaton::vivir(){
	//Tiro 3 rayos aproximadamente sobre la vista del raton.
	b2Vec2 point1, r2p1, r2p2;
	b2Vec2 point2, r3p1, r3p2;

	if (entidad.estadoNormal()) {
		point1 = b2Vec2(cuerpo->GetPosition().x+radio, cuerpo->GetPosition().y);
		point2 = b2Vec2(cuerpo->GetPosition().x+radio+Constantes::Instancia()->distanciaMinimaQueso, cuerpo->GetPosition().y);
		r2p1 = b2Vec2(cuerpo->GetPosition().x+radio, cuerpo->GetPosition().y+entidad.tamanio().y/2);
		r2p2 = b2Vec2(cuerpo->GetPosition().x+radio+Constantes::Instancia()->distanciaMinimaQueso,
																		cuerpo->GetPosition().y+entidad.tamanio().y/2);
		r3p1 = b2Vec2(cuerpo->GetPosition().x+radio, cuerpo->GetPosition().y-entidad.tamanio().y/2);
		r3p2 = b2Vec2(cuerpo->GetPosition().x+radio+Constantes::Instancia()->distanciaMinimaQueso,
																		cuerpo->GetPosition().y-entidad.tamanio().y/2);

	} else {
		point1 = b2Vec2(cuerpo->GetPosition().x-radio, cuerpo->GetPosition().y);
		point2 = b2Vec2(cuerpo->GetPosition().x-radio-Constantes::Instancia()->distanciaMinimaQueso, cuerpo->GetPosition().y);
		r2p1 = b2Vec2(cuerpo->GetPosition().x-radio, cuerpo->GetPosition().y+entidad.tamanio().y/2);
		r2p2 = b2Vec2(cuerpo->GetPosition().x-radio-Constantes::Instancia()->distanciaMinimaQueso,
																	cuerpo->GetPosition().y+entidad.tamanio().y/2);
		r3p1 = b2Vec2(cuerpo->GetPosition().x-radio, cuerpo->GetPosition().y-entidad.tamanio().y/2);
		r3p2 = b2Vec2(cuerpo->GetPosition().x-radio-Constantes::Instancia()->distanciaMinimaQueso,
																cuerpo->GetPosition().y-entidad.tamanio().y/2);
	}

	RayCastQueso callback(entidad);
	RayCastQueso callback2(entidad);
	RayCastQueso callback3(entidad);
	m_mundo->RayCast(&callback, point1, point2);
	m_mundo->RayCast(&callback2, r2p1, r2p2);
	m_mundo->RayCast(&callback3, r3p1, r3p2);

	if (callback.veQueso() || callback2.veQueso() ||  callback3.veQueso()) {
		this->rJoint->SetMotorSpeed((sentido)*Constantes::Instancia()->motorSpeed);
		this->entidad.accionar() = true;
	} else {
		this->rJoint->SetMotorSpeed(0);
		this->entidad.accionar() = false;
	}
}

MotorRaton::~MotorRaton() {
}
}

