/*
 * Cuerpo.cpp
 *
 *  Created on: Oct 4, 2013
 *      Author: lucia
 */

#include "Cuerpo.h"

namespace simulador {

Cuerpo::Cuerpo()
	: entidad()
	, cuerpo(nullptr)
	, posicionInicial()
	, m_mundo(nullptr)
{
}

Cuerpo::Cuerpo(Modelo::EntidadWrapper entidad, b2Body *cuerpo, Vec2 posicionInicial, b2World *m_mundo)
	: entidad(entidad)
	, cuerpo(cuerpo)
	, posicionInicial(posicionInicial)
	, m_mundo(m_mundo)
{
}

Cuerpo::~Cuerpo() {
}

void Cuerpo::tocarse(Cuerpo*, b2World*) {
}

void Cuerpo::conectarA(simulador::Engranaje*, b2World*) {
}

void Cuerpo::destruir(){
}

void Cuerpo::modelarContacto(){
}
} /* namespace simulador */
