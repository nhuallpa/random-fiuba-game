/*
 * Huevo.cpp
 *
 *  Created on: 03/11/2013
 *      Author: stephanie
 */

#include "Huevo.h"
#include "Sonido/Sonido.h"
#include "Simulador/Constantes.h"
#include <math.h>

namespace simulador {

#define VELOCIDAD_MINIMA_PARA_ROMPER_HUEVO 2

Huevo::Huevo(b2World* mundo, Modelo::EntidadWrapper entidad)
	: seRompio(false)
	, anguloInicial(entidad.angulo())
{
	this->m_mundo = mundo;
	this->entidad = entidad;
	this->entidad.accionar() = false;
	this->entidad.estadoNormal() = true;
	this->posicionInicial = entidad.centro();
	this->cuerpo = crearCuerpo();
	this->cuerpo->SetUserData(this);
}

Huevo::~Huevo() {
}

void Huevo::vivir(){
	if (entidad.valido()){
		if (!entidad.accionar()){
			entidad.angulo() = cuerpo->GetAngle() * Constantes::Instancia()->RADTODEG;
			entidad.centro() = Vec2(cuerpo->GetPosition());
		}else{
			entidad.borrar();
			m_mundo->DestroyBody(cuerpo);
		}
	}

}

b2Body* Huevo::crearCuerpo(){
	b2CircleShape circleShape;
	circleShape.m_p.Set(0,0);
	circleShape.m_radius = entidad.radio();

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &circleShape;
	fixtureDef.density = 1.0f;
	fixtureDef.restitution = 0.0f;

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(entidad.centro().x, entidad.centro().y);

	b2Body* body = m_mundo->CreateBody(&bodyDef);
	body->CreateFixture(&fixtureDef);

	return body;
}

void Huevo::destruir(){
	if (!seRompio)
		Sonido::Instancia()->playSound(entidad);
	seRompio = true;
	entidad.estadoNormal() = false;
}

void Huevo::modelarContacto(b2Contact* contact){
	contact->SetRestitution(0.0f); //para que no rebote el huevo
	b2Body* a = contact->GetFixtureA()->GetBody();
	b2Body* b = contact->GetFixtureB()->GetBody();

	void* data_a = a->GetUserData();
	void* data_b = b->GetUserData();

	if(!entidad.valido())
		return;

	Cuerpo* otroCuerpo;
	if (a == this->cuerpo){
		if (data_b){
			otroCuerpo = static_cast<Cuerpo*> (data_b);
		} else {
			return;
		}
	} else {
			if (data_a){
				otroCuerpo = static_cast<Cuerpo*> (data_a);
			} else {
				return;
			}
	}
	if (otroCuerpo->entidad.clase() != Modelo::TipoElemento::Globo && otroCuerpo->entidad.clase() != Modelo::TipoElemento::Soga){
		//Si la velocidad de las dos partes es muy chica no me rompo.
		Vec2 v1(otroCuerpo->getCuerpo()->GetLinearVelocity());
		Vec2 v2(this->getCuerpo()->GetLinearVelocity());
		if (v1.abs() > VELOCIDAD_MINIMA_PARA_ROMPER_HUEVO || v2.abs() > VELOCIDAD_MINIMA_PARA_ROMPER_HUEVO) {
			if(contact->IsTouching()) {
				destruir();
				if (otroCuerpo->entidad.clase() == Modelo::TipoElemento::Huevo) {
					otroCuerpo->destruir();
				}
			}
		}
	}
}

} /* namespace simulador */
