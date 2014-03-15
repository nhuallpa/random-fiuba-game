/*
 * Clavo.cpp
 *
 *  Created on: 01/11/2013
 *      Author: stephanie
 */

#include "Clavo.h"
#include "Simulador/Constantes.h"
#include <Box2D/Box2D.h>

namespace simulador {

Clavo::Clavo(b2World* mundo, Modelo::EntidadWrapper entidad)
	: anguloInicial (entidad.angulo())
{
	this->m_mundo = mundo;
	this->entidad = entidad;
	this->cuerpo = crearCuerpo();
	this->cuerpo->SetUserData(this);
}

Clavo::~Clavo() {
	m_mundo->DestroyBody(cuerpo);
}

b2Body* Clavo::crearCuerpo(){
	Vec2 posicion = entidad.centro();
	Vec2 dimensiones = entidad.tamanio() / 2;

	b2PolygonShape polygon1;
    polygon1.SetAsBox(dimensiones.x/8, dimensiones.y);
    b2FixtureDef fixtureDef1;
    fixtureDef1.shape = &polygon1;
    fixtureDef1.density = 1;

    //la base del clavo
    b2PolygonShape polygon2;
    polygon2.SetAsBox(dimensiones.x, 0.001f, b2Vec2(0.0f, dimensiones.y), 0);
    b2FixtureDef fixtureDef2;
    fixtureDef2.shape = &polygon2;
    fixtureDef2.density = 2;

    //la punta del clavo
	b2PolygonShape polygon3;
    polygon3.SetAsBox(dimensiones.x/8, 0, b2Vec2(0.0f, -dimensiones.y), 0);
    b2FixtureDef fixtureDef3;
    fixtureDef3.shape = &polygon3;
    fixtureDef3.density = 1;
    fixtureDef3.filter.categoryBits = 0x0004;

    b2BodyDef bd;
    bd.type = b2_staticBody;
    bd.angle = anguloInicial * Constantes::Instancia()->DEGTORAD;
    bd.position.Set(posicion.x,posicion.y);
    b2Body* body = m_mundo->CreateBody(&bd);
    body->CreateFixture(&fixtureDef1);
    body->CreateFixture(&fixtureDef2);
    body->CreateFixture(&fixtureDef3);
    return body;

}

} /* namespace simulador */
