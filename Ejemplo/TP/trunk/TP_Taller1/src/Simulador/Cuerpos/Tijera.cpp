/*
 * Tijera.cpp
 *
 *  Created on: 01/11/2013
 *      Author: stephanie
 */

#include "Tijera.h"
#include "Simulador/Constantes.h"
#include "Sonido/Sonido.h"
#include "Box2D/Box2D.h"
#include "Simulador/JointMaker.h"
#include "Soga.h"
#include "Polea.h"
#include <cmath>

namespace simulador {

Tijera::Tijera(b2World* mundo, Modelo::EntidadWrapper entidad)
	: soga1()
	, soga2()
	, cantidadDeVecesCerrado(0)
	, cuerpoCortante(nullptr)
	, soporte(nullptr)
	, joint (nullptr)
	, delay(0)
	, cuerpoDeCostado(nullptr)
{
	this->m_mundo = mundo;
	this->entidad = entidad;
	this->posicionInicial = entidad.centro();
	this->cuerpo = crearCuerpo();

	std::list<Modelo::EntidadWrapper> sogasAtadas = entidad.elemPuenteAtado();
	std::list<Modelo::EntidadWrapper>::iterator it;

	if (sogasAtadas.size() == 1) {
		it = sogasAtadas.begin();
		soga1 = *it;
	}else if (sogasAtadas.size() == 2) {
			it = sogasAtadas.begin();
			soga1 = *it;
			++it;
			soga2 = *it;
	}

	this->cuerpo->SetUserData(this);
}

MangoAtado Tijera::mapMangoSoga(Modelo::EntidadWrapper soga) {
	//1 soga y 2 sogas
	Vec2 miCentro = entidad.centro();
	Vec2 puntoLigadura;
	if(soga.entidadExtremoA() == this->entidad) {
		puntoLigadura = soga.puntoDeLigaduraEntidadA();
	} else {
		puntoLigadura = soga.puntoDeLigaduraEntidadB();
	}
	if ((entidad.angulo() == 0) || (entidad.angulo() == 180)){
		if(puntoLigadura.y < miCentro.y) {
			return MangoAtado::mango_arriba;
		} else {
			return MangoAtado::mango_abajo;
		}
	} else if((entidad.angulo() == 90)||(entidad.angulo() == 270)) {
		if (puntoLigadura.x > miCentro.x) {
			return MangoAtado::mango_derecho;
		} else {
			return MangoAtado::mango_izquierdo;
		}
	}
	return MangoAtado::mango_arriba;
}

Tijera::~Tijera() {
	m_mundo->DestroyBody(this->cuerpo);
}

b2Body* Tijera::crearCuerpo(){
	Vec2 dimensiones = entidad.tamanio() / 2;
	Vec2 posicion = entidad.centro();

	b2PolygonShape polygon1;
	polygon1.SetAsBox(0.4*dimensiones.x, 0.1*dimensiones.y, b2Vec2(-0.4*dimensiones.x,-0.5*dimensiones.y), 30*Constantes::Instancia()->DEGTORAD);

	b2FixtureDef fixture1;
	fixture1.shape = &polygon1;
//	fixture1.density = 0.5f;

	b2PolygonShape polygon2;
	polygon2.SetAsBox(0.4*dimensiones.x, 0.1*dimensiones.y, b2Vec2(-0.4*dimensiones.x,0.5*dimensiones.y), -30*Constantes::Instancia()->DEGTORAD);

	b2FixtureDef fixture2;
	fixture2.shape = &polygon2;

	b2PolygonShape polygon3;
	polygon3.SetAsBox(0.4*dimensiones.x, 0.1*dimensiones.y, b2Vec2(0.4*dimensiones.x, 0.4*dimensiones.y), 30*Constantes::Instancia()->DEGTORAD);

	b2FixtureDef fixture3;
	fixture3.shape = &polygon3;

	b2PolygonShape polygon4;
	polygon4.SetAsBox(0.4*dimensiones.x, 0.1*dimensiones.y, b2Vec2(0.4*dimensiones.x, -0.3*dimensiones.y), -30*Constantes::Instancia()->DEGTORAD);

	b2FixtureDef fixture4;
	fixture4.shape = &polygon4;

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.angle = entidad.angulo()*Constantes::Instancia()->DEGTORAD;
	bodyDef.position.Set(posicion.x, posicion.y);

	//uso estos edge para detectar el contacto con la pelota, yunque, etc
	b2PolygonShape ed1; //b2Vec2(0,dimensiones.y)
	ed1.SetAsBox(dimensiones.x,0,b2Vec2(0,-1.1*dimensiones.y),0);
	b2FixtureDef fixture5;
	fixture5.shape = &ed1;
	fixture5.filter.categoryBits = 0x0010;
	fixture5.isSensor = true;

	b2PolygonShape ed2;
	ed2.SetAsBox(dimensiones.x,0,b2Vec2(0,1.1*dimensiones.y),0);
	b2FixtureDef fixture6;
	fixture6.shape = &ed2;
	fixture6.filter.categoryBits = 0x0010;
	fixture6.isSensor = true;

	//agrego a los costados de la tijera
	b2PolygonShape polygonShape5;
	polygonShape5.SetAsBox(0,0.8*dimensiones.y, b2Vec2(-0.5*dimensiones.x, 0), 0);
	b2PolygonShape polygonShape6;
	polygonShape6.SetAsBox(0,0.6*dimensiones.y, b2Vec2(0.6*dimensiones.x, 0), 0);
	b2BodyDef bodyDef3;
	bodyDef3.type = b2_staticBody;
	bodyDef3.position.Set(posicion.x, posicion.y);
	bodyDef3.angle = entidad.angulo()*Constantes::Instancia()->DEGTORAD;
	cuerpoDeCostado = m_mundo->CreateBody(&bodyDef3);
	cuerpoDeCostado->CreateFixture(&polygonShape5, 0.0f);
	cuerpoDeCostado->CreateFixture(&polygonShape6, 0.0f);

	b2Body* body = m_mundo->CreateBody(&bodyDef);
	body->CreateFixture(&fixture1);
	body->CreateFixture(&fixture2);
	body->CreateFixture(&fixture3);
	body->CreateFixture(&fixture4);
	body->CreateFixture(&fixture5);
	body->CreateFixture(&fixture6);
	fixture1.density = 1.0f;
	fixture2.density = 1.0f;
	fixture3.density = 1.0f;
	fixture4.density = 1.0f;
	fixture5.density = 1.0f;
	fixture6.density = 1.0f;

	b2CircleShape circle;
	circle.m_radius = 0;
	b2BodyDef bodyDef2;
	bodyDef2.type = b2_staticBody;
	bodyDef2.position = body->GetWorldCenter();
	b2Body* soporte = m_mundo->CreateBody(&bodyDef2);
	soporte->CreateFixture(&circle, 0);
	JointMaker::crearRevoluteJoint(m_mundo, soporte, body, false, 0, 0);
	return body;
}

void Tijera::vivir(){
	modelarContacto();
}

b2Body* Tijera::cerrarTijera(){
	Vec2 tamanio = entidad.tamanio() / 2;
	Vec2 posicion = entidad.centro();
	b2PolygonShape polygon1;
	polygon1.SetAsBox(0.5*tamanio.x, tamanio.y/4, b2Vec2(0.25*tamanio.x,0), 0);

	b2FixtureDef fixture1;
	fixture1.shape = &polygon1;

	b2PolygonShape polygon2;
	polygon2.SetAsBox(0.2*tamanio.x, tamanio.y/4, b2Vec2(-0.6*tamanio.x,-0.4*tamanio.y), 0);

	b2FixtureDef fixture2;
	fixture2.shape = &polygon2;

	b2PolygonShape polygon3;
	polygon3.SetAsBox(0.2*tamanio.x, tamanio.y/4, b2Vec2(-0.6*tamanio.x,0.4*tamanio.y), 0);

	b2FixtureDef fixture3;
	fixture3.shape = &polygon3;

	b2BodyDef bodyDef1;
	bodyDef1.type = b2_staticBody;
	bodyDef1.angle = entidad.angulo() * Constantes::Instancia()->DEGTORAD;
	bodyDef1.position.Set(posicion.x, posicion.y);

	b2Body* body = m_mundo->CreateBody(&bodyDef1);
	body->CreateFixture(&fixture1);
	body->CreateFixture(&fixture2);
	body->CreateFixture(&fixture3);

	//creo un cuerpito en el costado
	b2PolygonShape polygon4;
	polygon4.SetAsBox(0.3*tamanio.x,0.1*tamanio.y, b2Vec2(0.5*tamanio.x,0),0);//(0.4*tamanio.x, 0);
	b2FixtureDef fixture4;
	fixture4.shape = &polygon4;
	fixture4.filter.categoryBits = 0x0002;
	b2BodyDef bodyDef2;
	bodyDef2.position = body->GetWorldCenter();
	bodyDef2.type = b2_dynamicBody;
	bodyDef2.angle = entidad.angulo() * Constantes::Instancia()->DEGTORAD;
	b2Body* body2 = m_mundo->CreateBody(&bodyDef2);
	body2->CreateFixture(&fixture4);
	cuerpoCortante = body2;

	b2CircleShape circle;
	circle.m_radius = 0;
	b2BodyDef bodyDef3;
	bodyDef3.type = b2_staticBody;
	bodyDef3.position = body2->GetWorldCenter();
	b2Body* soporte = m_mundo->CreateBody(&bodyDef3);
	soporte->CreateFixture(&circle, 0);
	this->soporte = soporte;
	joint = JointMaker::crearRevoluteJoint(m_mundo, soporte, body2, false, 0, 0);
	return body;
}

void Tijera::modelarContacto(){
	if (entidad.estadoNormal()){
		modelarContactoCuerpoTijera();
		controlarTension();
	}else{
		modelarContactoCuerpoCortante();
	}
}

void Tijera::modelarContactoCuerpoTijera(){
	if (cuerpo != nullptr){
		for (b2ContactEdge* ce = cuerpo->GetContactList(); ce; ce = ce->next){
			b2Body* otroCuerpo = ce->other;
			void* data = otroCuerpo->GetUserData();
			if (ce->contact->IsTouching()){
				if (data){
					Cuerpo* otro = static_cast<Cuerpo*>(data);
					if (!otro->entidad.valido()) {
						break;
					}
					if (otro->entidad.clase() == Modelo::TipoElemento::PelotaBasquet ||
							otro->entidad.clase() == Modelo::TipoElemento::PelotaBowling ||
							otro->entidad.clase() == Modelo::TipoElemento::Yunque ||
							otro->entidad.clase() == Modelo::TipoElemento::Balancin ||
							otro->entidad.clase() == Modelo::TipoElemento::Carrito){
						if (ce->contact->GetFixtureA()->GetFilterData().categoryBits == 0x0010 ||
								ce->contact->GetFixtureB()->GetFilterData().categoryBits == 0x0010){
							if (entidad.angulo() == 0 || entidad.angulo() == 180){
								if (otro->cuerpo->GetLinearVelocity().y != 0){
									if (entidad.estadoNormal()){
										cantidadDeVecesCerrado++;
									}
									entidad.estadoNormal() = false;
									cambiarForma();
									break;
								}
							}else{
								if ((otro->cuerpo->GetLinearVelocity().x != 0) &&
										(otro->cuerpo->GetLinearVelocity().y < otro->cuerpo->GetLinearVelocity().x)){
									if (entidad.estadoNormal()){
										cantidadDeVecesCerrado++;
									}
									entidad.estadoNormal() = false;
									cambiarForma();
									break;
								}
							}
						}
					}
				}
			}
		}
	}
}

void Tijera::modelarContactoCuerpoCortante(){
	if (cuerpoCortante != nullptr){
		for (b2ContactEdge* ce = cuerpoCortante->GetContactList(); ce; ce = ce->next){
			b2Fixture* a = ce->contact->GetFixtureA();
			b2Fixture* b = ce->contact->GetFixtureB();

			b2Body* otroCuerpo = ce->other;
			void* data = otroCuerpo->GetUserData();
			if (ce->contact->IsTouching()){
				if (data){
					Cuerpo* otro = static_cast<Cuerpo*>(data);
					if (otro->entidad.clase() == Modelo::TipoElemento::Soga){
						Soga* soga = dynamic_cast<Soga*> (buscarCuerpoEnMundo(otro->entidad));
						if (soga != nullptr){
							if (soga->entidad.entidadExtremoA().clase() == Modelo::TipoElemento::Polea){
								Polea* polea = dynamic_cast<Polea*> (buscarCuerpoEnMundo(soga->entidad.entidadExtremoA()));
								if (polea != nullptr){
									if (cantidadDeVecesCerrado == 1){
										if (a->GetFilterData().categoryBits == 0x0002 || b->GetFilterData().categoryBits == 0x0002){
											polea->romperAparejo();
											destruirCuerpoCortante();
											break;
										}
									}
								}
							}else
								if (soga->entidad.entidadExtremoB().clase() == Modelo::TipoElemento::Polea){
									Polea* polea = dynamic_cast<Polea*> (buscarCuerpoEnMundo(soga->entidad.entidadExtremoB()));
									if (polea != nullptr){
										if (cantidadDeVecesCerrado == 1){
											if (a->GetFilterData().categoryBits == 0x0002 || b->GetFilterData().categoryBits == 0x0002){
												polea->romperAparejo();
												destruirCuerpoCortante();
												break;
											}
										}
									}
							}else{
								if (cantidadDeVecesCerrado == 1){
									if (a->GetFilterData().categoryBits == 0x0002 || b->GetFilterData().categoryBits == 0x0002){
										dynamic_cast<Soga*> (otro)->cortarSoga();
										destruirCuerpoCortante();
										break;
									}
								}
							}
						}
					}else{
						if (delay > 3){
							destruirCuerpoCortante();
							break;
						}
						delay++;
					}
				}
			}
		}
	}
}

void Tijera::controlarTension(){

	controlarTensionDosSogas();

}

b2Vec2 Tijera::getReactionForce(Modelo::EntidadWrapper sogaReq) {
	Soga* soga = dynamic_cast<Soga*> (buscarCuerpoEnMundo(sogaReq));
	float timeStep = 1/Constantes::Instancia()->iteracionesPorSegundo;
	b2RopeJoint* ropeJoint;
	b2Vec2 reactionForce(0,0);
	if (soga != nullptr){
		if ((soga->entidad.entidadExtremoA().clase() == Modelo::TipoElemento::Polea) ||
				(soga->entidad.entidadExtremoB().clase() == Modelo::TipoElemento::Polea)){
			Polea* polea;
			if (soga->entidad.entidadExtremoA().clase() == Modelo::TipoElemento::Polea) {
				polea = dynamic_cast<Polea*> (buscarCuerpoEnMundo(soga->entidad.entidadExtremoA()));
			} else {
				polea = dynamic_cast<Polea*> (buscarCuerpoEnMundo(soga->entidad.entidadExtremoB()));
			}
			reactionForce = polea->getReactionForce(this);

		}else{
			ropeJoint = soga->getRopeJoint();
			if (ropeJoint != nullptr)
				if(ropeJoint->GetBodyB() == this->getCuerpo()) {
					reactionForce = b2Vec2(ropeJoint->GetReactionForce(timeStep));
				} else {
					reactionForce = (-1)*ropeJoint->GetReactionForce(timeStep);
				}

			else {

			}
		}
	}
	float fuerzaMinima = 0.05;
	if (!(sogaReq.entidadExtremoA().clase() == Modelo::TipoElemento::Globo) &&
			!(sogaReq.entidadExtremoB().clase() == Modelo::TipoElemento::Globo)) {

			if(fabs(reactionForce.x) < fuerzaMinima) {
				reactionForce = b2Vec2(0,reactionForce.y);
			}
			if(fabs(reactionForce.y) < fuerzaMinima) {
				reactionForce = b2Vec2(reactionForce.x,0);
			}

	}
	return reactionForce;
}

void Tijera::controlarTensionDosSogas(){
	b2Vec2 fuerzaSoga1;
	b2Vec2 fuerzaSoga2;
	std::pair<Modelo::EntidadWrapper, MangoAtado> sogaYMango1;
	std::pair<Modelo::EntidadWrapper, MangoAtado> sogaYMango2;
	if(soga1.valido()) {
		fuerzaSoga1 = getReactionForce(soga1);
		MangoAtado m1 = mapMangoSoga(soga1);
		sogaYMango1 = std::make_pair(soga1,m1);
	}
	if (soga1.valido() && soga2.valido()) {
		fuerzaSoga2 = getReactionForce(soga2);
		MangoAtado m2 = mapMangoSoga(soga2);
		sogaYMango2 = std::make_pair(soga2,m2);

	}
	if(soga1.valido() && estaTirando(sogaYMango1,fuerzaSoga1)) {
		entidad.estadoNormal() = false;
		cantidadDeVecesCerrado++;
		cambiarForma();
	}
	if (soga2.valido() && estaTirando(sogaYMango2,fuerzaSoga2)) {
		entidad.estadoNormal() = false;
		cantidadDeVecesCerrado++;
		cambiarForma();
	}
}

bool Tijera::estaTirando(std::pair<Modelo::EntidadWrapper, MangoAtado> soga, b2Vec2 fuerza){
	float minimaFuerza = 0;
	MangoAtado mango = soga.second;
	bool tira = false;
	switch(mango) {
	case MangoAtado::mango_abajo: {
		if ((entidad.angulo() == 0)) {
			tira = (fuerza.y < minimaFuerza ) ? true : false;
		} else if ((entidad.angulo() == 180)) {
			tira = (fuerza.y < minimaFuerza ) ? true : false;
		}
		break;
	} case MangoAtado::mango_arriba: {
		if((entidad.angulo() == 0)) {
			tira = (fuerza.y > minimaFuerza) ? true : false;
		} else if ((entidad.angulo() == 180)){
			tira = (fuerza.y > minimaFuerza) ? true : false;
		}
		break;
	} case MangoAtado::mango_derecho: {
		if((entidad.angulo() == 90)) {
			tira = (fuerza.x < minimaFuerza) ? true : false;
		} else if(entidad.angulo() == 270)
			tira = (fuerza.x < minimaFuerza) ? true : false;
		break;
	} case MangoAtado::mango_izquierdo: {
		if((entidad.angulo() == 90)) {
			tira = (fuerza.x > minimaFuerza) ? true : false;
		} else if(entidad.angulo() == 270)
			tira = (fuerza.x > minimaFuerza) ? true : false;
		break;
	}
	}
	return tira;
}

void Tijera::destruirCuerpoCortante(){
	m_mundo->DestroyJoint(joint);
	m_mundo->DestroyBody(cuerpoCortante);
	cuerpoCortante = nullptr;
	m_mundo->DestroyBody(soporte);
}

void Tijera::cambiarForma(){
	if (cantidadDeVecesCerrado == 1){
		if (entidad.elemPuenteAtado().size() == 0){
			m_mundo->DestroyBody(cuerpo);
			m_mundo->DestroyBody(cuerpoDeCostado);
			cuerpo = cerrarTijera();
			cuerpo->SetUserData(this);
		}
		if (entidad.elemPuenteAtado().size() == 1){
			Soga* sogaActual = dynamic_cast<Soga*> (buscarCuerpoEnMundo(soga1));
			if (sogaActual != nullptr){
				b2RopeJoint* ropeJoint = sogaActual->getRopeJoint();
				b2Body* a = ropeJoint->GetBodyA();
				b2Body* b = ropeJoint->GetBodyB();
				if (a == cuerpo){
					cambiarACuerpoTijeraConSensor();
					cuerpo = cerrarTijera();
					cuerpo->SetUserData(this);
					a = cuerpo;
					sogaActual->entidad.lugarDondeSePuedeUnir();
				}
				if (b == cuerpo){
					cambiarACuerpoTijeraConSensor();
					cuerpo = cerrarTijera();
					cuerpo->SetUserData(this);
					b = cuerpo;
					sogaActual->entidad.lugarDondeSePuedeUnir();
				}
			}
		}

		if (entidad.elemPuenteAtado().size() == 2){
			Soga* sogaActual1 = dynamic_cast<Soga*> (buscarCuerpoEnMundo(soga1));
			Soga* sogaActual2 = dynamic_cast<Soga*> (buscarCuerpoEnMundo(soga2));
			if (sogaActual1 != nullptr && sogaActual2 != nullptr){
				b2RopeJoint* ropeJoint = sogaActual1->getRopeJoint();
				b2Body* a = ropeJoint->GetBodyA();
				b2Body* b = ropeJoint->GetBodyB();
				if (a == cuerpo){
					cambiarACuerpoTijeraConSensor();
					cuerpo = cerrarTijera();
					cuerpo->SetUserData(this);
					a = cuerpo;
				}
				if (b == cuerpo){
					cambiarACuerpoTijeraConSensor();
					cuerpo = cerrarTijera();
					cuerpo->SetUserData(this);
					b = cuerpo;
				}

				b2RopeJoint* ropeJoint2 = sogaActual2->getRopeJoint();
				b2Body* a2 = ropeJoint2->GetBodyA();
				b2Body* b2 = ropeJoint2->GetBodyB();
				if (a2 == cuerpo)
					a2 = cuerpo; //solo esto xq ya cerre la tijera
				if (b2 == cuerpo)
					b2 = cuerpo;
			}
		}
		Sonido::Instancia()->playSound(entidad);
	}
}

Cuerpo* Tijera::buscarCuerpoEnMundo(Modelo::EntidadWrapper entidad) {

	for ( b2Body* b = m_mundo->GetBodyList(); b; b = b->GetNext())
	{
		void* data1 = b->GetUserData();
		if (data1) {
			Cuerpo* body1 = static_cast<Cuerpo*> (data1);
			if (body1->entidad == entidad) {
				return body1;
			}
		}
	}
	//TODO tirar exception
	return nullptr;
}

void Tijera::cambiarACuerpoTijeraConSensor(){
	for (b2Fixture* fix = cuerpo->GetFixtureList(); fix; fix = fix->GetNext()){
		fix->SetSensor(true);
	}
	m_mundo->DestroyBody(cuerpoDeCostado);
}
} /* namespace simulador */
