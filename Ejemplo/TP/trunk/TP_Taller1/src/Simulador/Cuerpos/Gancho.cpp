/*
 * Gancho.cpp
 *
 *  Created on: Nov 2, 2013
 *      Author: lucia
 */

#include "Gancho.h"

namespace simulador {

Gancho::Gancho(b2World* mundo, Modelo::EntidadWrapper entidad) {
	m_mundo = mundo;
	this->entidad = entidad;
	cuerpo = crearCuerpo();
	this->cuerpo->SetUserData(this);
}

b2Body* Gancho::crearCuerpo(){
	b2BodyDef myBodyDef;
	myBodyDef.type = b2_staticBody;
	myBodyDef.position.Set(entidad.centro().x, entidad.centro().y);
	b2Body* gancho = m_mundo->CreateBody(&myBodyDef);
	b2PolygonShape circleShape;
	circleShape.SetAsBox(entidad.tamanio().x/2, entidad.tamanio().y/2);
	b2FixtureDef myFixtureDef;
	myFixtureDef.shape = &circleShape;
	myFixtureDef.density = Constantes::Instancia()->densidadGancho;
	gancho->CreateFixture(&myFixtureDef);
	return gancho;
}

Gancho::~Gancho() {
	m_mundo->DestroyBody(cuerpo);
}

} /* namespace simulador */
