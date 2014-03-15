/*
 * Balancin.cpp
 *
 *  Created on: Oct 4, 2013
 *      Author: lucia
 */

#include "Balancin.h"

#include "Simulador/Constantes.h"
#include <Box2D/Box2D.h>

namespace simulador {

Balancin::Balancin(b2World* mundo, Modelo::EntidadWrapper entidad)
	: dimensiones(entidad.tamanio() / 2)
	, soporte(soporte)
	, anguloInicial(entidad.angulo())
{
	this->posicionInicial = entidad.centro();
	this->cuerpo = crearCuerpo(mundo);
	this->soporte = crearSoporte(cuerpo, mundo);
	this->entidad = entidad;
	this->crearJuntura(cuerpo,soporte,mundo);
	//cambio el userData
	this->cuerpo->SetUserData(this);
	this->m_mundo = mundo;

}

b2Body* Balancin::crearSoporte(b2Body* plataforma,b2World* mundo) {
	b2FixtureDef pin;
	b2PolygonShape cuadrado;
	cuadrado.SetAsBox(Constantes::Instancia()->radioSoporte,Constantes::Instancia()->radioSoporte);
	pin.shape=&cuadrado;
	b2BodyDef soporteDef;
	soporteDef.type = b2_staticBody;
	soporteDef.position=plataforma->GetWorldCenter();
	b2Body* soporte = mundo->CreateBody(&soporteDef);
	soporte->CreateFixture(&pin);
	return soporte;
}

b2Body* Balancin::crearCuerpo(b2World* mundo) {
	//Plataforma del subibaja.
	b2FixtureDef plataforma;
	plataforma.density=50;
	plataforma.restitution=1;
	b2PolygonShape boxShape;
	boxShape.SetAsBox(dimensiones.x, dimensiones.y);
	plataforma.shape = &boxShape;
	//Creo el cuerpo
	b2BodyDef defBalancin;
	defBalancin.type = b2_dynamicBody;
	defBalancin.position.Set(posicionInicial.x, posicionInicial.y);
	defBalancin.angle=(this->anguloInicial*Constantes::Instancia()->DEGTORAD);
	b2Body* balancin = mundo->CreateBody(&defBalancin);
	balancin->CreateFixture(&plataforma);
	return balancin;
}

void Balancin::crearJuntura(b2Body* plataforma, b2Body* soporte, b2World* mundo) {
	b2RevoluteJointDef revoluteJointDef;
	revoluteJointDef.bodyA = plataforma;
	revoluteJointDef.bodyB = soporte;
	revoluteJointDef.collideConnected = false;
	revoluteJointDef.localAnchorB.Set(0,Constantes::Instancia()->radioSoporte);
	revoluteJointDef.enableLimit = true;
	//revoluteJointDef.enableMotor = true;
	//revoluteJointDef.maxMotorTorque = 50;
	//revoluteJointDef.motorSpeed = 0.0f;
	revoluteJointDef.lowerAngle = -45 * Constantes::Instancia()->DEGTORAD;
	revoluteJointDef.upperAngle =  45 * Constantes::Instancia()->DEGTORAD;
	mundo->CreateJoint( &revoluteJointDef );
}

Balancin::~Balancin() {
	m_mundo->DestroyBody(soporte);
	m_mundo->DestroyBody(cuerpo);
}

void Balancin::vivir(){
	entidad.angulo() = cuerpo->GetAngle() * Constantes::Instancia()->RADTODEG;
}

} /* namespace simulador */
