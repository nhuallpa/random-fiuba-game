/*
 * CintaTransportadora.cpp
 *
 *  Created on: 04/10/2013
 *      Author: stephanie
 */

#include "CintaTransportadora.h"

#include "Simulador/JointMaker.h"
#include "Engranaje.h"
#include <Box2D/Box2D.h>
#include <math.h>
#include <iostream>
namespace simulador {

CintaTransportadora::CintaTransportadora(b2World* mundo, Modelo::EntidadWrapper entidad)
	: posicion(entidad.centro())
	, dimensiones(entidad.tamanio() / 2)
	, rectArriba(nullptr)
	, rectAbajo(nullptr)
	, gear1(nullptr)
	, gear2(nullptr)
	, impulso(0)
	, conectadoACuerpo(nullptr)
	, velocidad(0)
	, engranajesSeteados(false)
{
	this->posicionInicial = posicion;
	this->m_mundo = mundo;
	this->crearCinta(mundo);
	//pongo que el cuerpo sea el rectagulo de arriba
	this->cuerpo = rectAbajo;
	this->entidad = entidad;
	//cambio el userData
	this->cuerpo->SetUserData(this);
}

CintaTransportadora::~CintaTransportadora() {
	m_mundo->DestroyBody(rectAbajo);
	m_mundo->DestroyBody(rectArriba);

}

void CintaTransportadora::crearCinta(b2World* mundo){
	//TODO: ver si/como pasar los new a construir desde el modelo
	float ancho = dimensiones.x;
	float alto = dimensiones.y;
	rectArriba = crearBox(posicion.x, posicion.y, ancho);
	rectArriba->SetUserData(this);
	rectAbajo = crearBox(posicion.x, posicion.y - alto*2, ancho);
	//b2Vec2 pos1(posicion.x - ancho + alto/2, posicion.y);
	b2Vec2 pos1(posicion.x - ancho + alto, posicion.y);
	gear1 = new Engranaje(pos1, m_mundo, 0, alto, true, false, entidad);
	gear1->cuerpo->SetUserData(this);
	//b2Vec2 pos2(posicion.x + ancho - alto/2, posicion.y);//-dimensiones.y);
	b2Vec2 pos2(posicion.x + ancho - alto, posicion.y);
	gear2 = new Engranaje(pos2, m_mundo, 0, alto, true, false, entidad);
	gear2->cuerpo->SetUserData(this);
}


b2Body* CintaTransportadora::crearBox(float x, float y, float ancho){
     b2FixtureDef fixture;
	 b2PolygonShape polygon;
	 //aca hago ancho - ancho/5 para que la plataforma se adapte mas a la figura
	 polygon.SetAsBox(ancho - dimensiones.y/2, 0);
	 fixture.shape = &polygon;
	 //Creo el cuerpo
	 b2BodyDef def;
	 def.type = b2_staticBody;
	 def.position.Set(x, y + dimensiones.y); //hago esta suma porque sino se crea muy abajo la plataforma ¬¬
	 	 	 	 	 //(x,y+o.5)	 	 	 //esto debido al setAsBox, por ese 0,00..01 que le pongo
	 	 	 	 	 	 	 	 //para que sea una plataforma super fina
	 b2Body* body = m_mundo->CreateBody(&def);
	 body->CreateFixture(&fixture);

	 return body;

}


void CintaTransportadora::vivir(){
	setearVelocidad();
	if (conectadoACuerpo && conectadoACuerpo->entidad.clase() != Modelo::TipoElemento::CintaTransportadora){
		if (conectadoACuerpo->entidad.clase() == Modelo::TipoElemento::Engranaje){
			velocidad*=(-1);
			if (conectadoACuerpo->cuerpo->GetAngularVelocity() != 0){
				gear1->getJoint()->EnableMotor(true);
				gear2->getJoint()->EnableMotor(true);
			}
			if (conectadoACuerpo->cuerpo->GetAngularVelocity() > 0){ //van en sentido horario
				if (engranajesSeteados){
					gear1->getJoint()->SetMotorSpeed(Constantes::Instancia()->motorSpeed);
					gear2->getJoint()->SetMotorSpeed(Constantes::Instancia()->motorSpeed);
				}


			}else{
				if (engranajesSeteados){
					gear1->getJoint()->SetMotorSpeed(-Constantes::Instancia()->motorSpeed);
					gear2->getJoint()->SetMotorSpeed(-Constantes::Instancia()->motorSpeed);
				}
			}
		}
		engranajesSeteados = true;
	}

	entidad.distanciaRecorrida() += velocidad / Constantes::Instancia()->iteracionesPorSegundo;
	modelarContacto();
}

void CintaTransportadora::modelarContacto(){
	for(b2Contact* contact = m_mundo->GetContactList(); contact; contact = contact->GetNext()){
		b2Body* a = contact->GetFixtureA()->GetBody();
		b2Body* b = contact->GetFixtureB()->GetBody();

		b2Vec2 aLinearVelocity = a->GetLinearVelocity();
		b2Vec2 bLinearVelocity = b->GetLinearVelocity();

		if (a == rectArriba){
			if (contact->IsTouching()){
				b->SetAwake(false);
	            b->SetLinearVelocity(b2Vec2(-velocidad,bLinearVelocity.y));
			}
		}
		if (b == rectArriba){
			if (contact->IsTouching()){
				a->SetAwake(false);
				a->SetLinearVelocity(b2Vec2(-velocidad,aLinearVelocity.y));
			}
		}

		if (a == rectAbajo){
			if (contact->IsTouching()){
				b->SetAwake(false);
				b->SetLinearVelocity(b2Vec2(velocidad,bLinearVelocity.y));
			}
		}

		if (b == rectAbajo){
			if (contact->IsTouching()){
				a->SetAwake(false);
				a->SetLinearVelocity(b2Vec2(velocidad,aLinearVelocity.y));
			}
		}
	}

}

void CintaTransportadora::setSentidoSegunCuerpoRotativo(CuerpoRotativo* cuerpoRotativo){
	conectadoACuerpo = cuerpoRotativo;
	if (conectadoACuerpo->entidad.clase() != Modelo::TipoElemento::CintaTransportadora &&
		conectadoACuerpo->entidad.clase() != Modelo::TipoElemento::Engranaje){
				gear1->getJoint()->EnableMotor(true);
				gear2->getJoint()->EnableMotor(true);
	}

	if (cuerpoRotativo->getSentidoHorario()){
		gear1->setSentidoAntihorario(true);
		gear2->setSentidoHorario(false);
		gear1->getJoint()->SetMotorSpeed(-Constantes::Instancia()->motorSpeed);
		gear2->getJoint()->SetMotorSpeed(-Constantes::Instancia()->motorSpeed);

	}else{
		gear1->setSentidoAntihorario(false);
		gear2->setSentidoHorario(true);
		gear1->getJoint()->SetMotorSpeed(Constantes::Instancia()->motorSpeed);
		gear2->getJoint()->SetMotorSpeed(Constantes::Instancia()->motorSpeed);
	}
}

void CintaTransportadora::setearVelocidad(){
	if (conectadoACuerpo){
		velocidad = -conectadoACuerpo->getCuerpo()->GetAngularVelocity()*0.3;
		entidad.estadoNormal() = velocidad > 0;
	}
}

} /* namespace simulador */
