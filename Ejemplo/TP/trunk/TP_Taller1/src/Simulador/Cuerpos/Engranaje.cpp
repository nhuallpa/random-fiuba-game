/*
 * Engranaje.cpp
 *
 *  Created on: 04/10/2013
 *      Author: stephanie
 */

#include "Engranaje.h"

#include "Simulador/JointMaker.h"
#include <Box2D/Box2D.h>

namespace simulador {

Engranaje::Engranaje(b2Vec2 posInicial, b2World* mundo, float angulo, float radio, bool sentidoHorario, bool sentidoAntihorario, Modelo::EntidadWrapper entidad)
	: CuerpoRotativo(posInicial, mundo, angulo, radio, sentidoHorario, sentidoAntihorario, false, entidad)
	, cuerposConectadosAMi()
{
	//cambio el userData
	this->cuerpo->SetUserData(this);
}

void Engranaje::tocarse(Cuerpo* otroCuerpo, b2World* mundo) {
	if(cuerposConectadosAMi.find(otroCuerpo) == cuerposConectadosAMi.end()) {
		otroCuerpo->conectarA((simulador::Engranaje*)this, mundo);
	}
}

void Engranaje::conectarA(Engranaje* eng, b2World* mundo) {
	b2Body* soporteEngranaje1 = eng->getSoporte();
	b2Joint* jointEngranaje1 = eng->getJoint();
	b2Body* miSoporte = this->soporte;
	b2Joint* miJoint = this->rJoint;
	float ratio = radio / eng->radio;

	JointMaker::crearGearJoint(mundo,soporteEngranaje1,miSoporte,jointEngranaje1,
			miJoint, ratio);
	if (cuerposConectadosAMi.empty()){
		//me fijo si el esta por conectarse a mi
	}
	this->cuerposConectadosAMi.insert(eng);
	eng->insertarConexion(this);

}

void Engranaje::insertarConexion(Cuerpo* otroCuerpo){
	this->cuerposConectadosAMi.insert(otroCuerpo);
}

Engranaje::~Engranaje() {
}

void Engranaje::vivir(){
	//esto igual me parece que hay que cambiar
	entidad.angulo() = cuerpo->GetAngle() * Constantes::Instancia()->RADTODEG;
}

} /* namespace simulador */
