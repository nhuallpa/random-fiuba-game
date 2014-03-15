/*
 * Motor.cpp
 *
 *  Created on: 04/10/2013
 *      Author: stephanie
 */

#include "Motor.h"

#include "Simulador/JointMaker.h"
#include <Box2D/Box2D.h>

namespace simulador {

Motor::Motor(b2World* mundo, Modelo::EntidadWrapper entidad)
	: CuerpoRotativo(entidad.centro(), mundo, entidad.angulo(), entidad.radio()/2,
	                 entidad.estadoNormal(), !entidad.estadoNormal(), true, entidad)
{
	//cambio el userData
	this->cuerpo->SetUserData(this);
	Vec2 p1;
	p1.x = entidad.centro().x - entidad.tamanio().x/2;
	p1.y = entidad.centro().y + entidad.tamanio().y/2;
	Vec2 p2;
	p2.x = entidad.centro().x + entidad.tamanio().x/2;
	p2.y = entidad.centro().y + entidad.tamanio().y/2;
	Vec2 p3;
	p3.x = entidad.centro().x - entidad.tamanio().x/2;
	p3.y = entidad.centro().y - entidad.tamanio().y/2;
	Vec2 p4;
	p4.x = entidad.centro().x + entidad.tamanio().x/2;
	p4.y = entidad.centro().y - entidad.tamanio().y/2;

	b2Body* cuerpo1 = JointMaker::crearEdge(p1, p2, mundo);
	b2Body* cuerpo2 = JointMaker::crearEdge(p3, p4, mundo);
	b2Body* cuerpo3 = JointMaker::crearEdge(p1, p3, mundo);
	b2Body* cuerpo4 = JointMaker::crearEdge(p2, p4, mundo);
	cuerpo1->SetUserData(this);
	cuerpo2->SetUserData(this);
	cuerpo3->SetUserData(this);
	cuerpo4->SetUserData(this);
}


Motor::~Motor() {
}

} /* namespace simulador */
