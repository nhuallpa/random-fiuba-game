/*
 * Plataforma.cpp
 *
 *  Created on: Oct 3, 2013
 *      Author: lucia
 */

#include "Plataforma.h"

#include "Simulador/Constantes.h"
#include <Box2D/Box2D.h>

namespace simulador {

Plataforma::Plataforma(b2World* mundo, Modelo::EntidadWrapper entidad)
	: dimensiones(entidad.tamanio() / 2)
	, angulo(entidad.angulo())
{
	this->posicionInicial = entidad.centro();
	this->cuerpo = crearCuerpo(mundo);
	this->entidad = entidad;
	//cambio el userData
	this->cuerpo->SetUserData(this);
	this->m_mundo = mundo;
}

b2Body* Plataforma::crearCuerpo(b2World* mundo){
	b2BodyDef myBodyDef;
	//La plataforma es estatica porque no se ve
	//afectada por el resto de los objetos del mundo.
	myBodyDef.type = b2_staticBody;
	myBodyDef.position.Set(posicionInicial.x, posicionInicial.y);
	myBodyDef.angle = this->angulo * Constantes::Instancia()->DEGTORAD;
	b2Body* cuerpoPlataforma = mundo->CreateBody(&myBodyDef);
	b2PolygonShape boxShape;
	boxShape.SetAsBox(dimensiones.x, dimensiones.y);
	b2FixtureDef boxFixtureDef;
	boxFixtureDef.shape = &boxShape;
	boxFixtureDef.density = 1;
	cuerpoPlataforma->CreateFixture(&boxFixtureDef);

	return cuerpoPlataforma;
}

Plataforma::~Plataforma() {
	m_mundo->DestroyBody(cuerpo);
}
} /* namespace simulador */
