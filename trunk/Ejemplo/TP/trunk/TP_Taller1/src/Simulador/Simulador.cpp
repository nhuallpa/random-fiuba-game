/*
 * Simulador.cpp
 *
 *  Created on: Oct 5, 2013
 *      Author: lucia
 */

#include "Simulador.h"
#include "Cuerpos/PelotaBasquet.h"
#include "Cuerpos/PelotaBowling.h"
#include "Cuerpos/Balancin.h"
#include "Cuerpos/Correa.h"
#include "Cuerpos/CintaTransportadora.h"
#include "Cuerpos/Engranaje.h"
#include "Cuerpos/Globo.h"
#include "Cuerpos/Motor.h"
#include "Cuerpos/Plataforma.h"
#include "Cuerpos/Soga.h"
#include "Cuerpos/Correa.h"
#include "Cuerpos/CuerpoRotativo.h"
#include "Cuerpos/Clavo.h"
#include "Cuerpos/Gancho.h"
#include "Cuerpos/Yunque.h"
#include "Cuerpos/Huevo.h"
#include "Cuerpos/Canio.h"
#include "Cuerpos/Codo.h"
#include "Cuerpos/Tijera.h"
#include "Cuerpos/Domino.h"
#include "Cuerpos/Queso.h"
#include "Cuerpos/PaletaFlipper.h"
#include "Cuerpos/Polea.h"
#include "Cuerpos/Vela.h"
#include "Cuerpos/Carrito.h"
#include "Cuerpos/Canasto.h"
#include "Cuerpos/MotorRaton.h"
#include "Modelo/EntidadWrapper.h"
#include "Modelo/Mundo.h"
#include "Modelo/TipoElemento.h"
#include "ContactListener.h"

namespace simulador {
Simulador::Simulador(Modelo::Mundo* mundo)
	: timeStep(1/Constantes::Instancia()->iteracionesPorSegundo)
	, velocityIterations(Constantes::Instancia()->nIteracionesVelocidades)
	, positionIterations(Constantes::Instancia()->nIteracionesPosiciones)
	, m_mundo()
	, cuerpos()
	, mundoModelo()
	, contactListener()
{
	modelarMundo(mundo);
	m_mundo->SetContactListener(&contactListener);
}

bool Simulador::step(){

	modelarContactos();

	//DAR UN PASO EN LA SIMULACION:
	m_mundo->Step( timeStep, velocityIterations, positionIterations);

	//TRADUCIRLO AL MODELO:
	std::list<Cuerpo*>::const_iterator iterator;
	for(iterator = cuerpos.begin();iterator != cuerpos.end(); ++iterator) {
		Cuerpo* cuerpo = *iterator;
		cuerpo->vivir();
	}
	return true;
}

float Simulador::getTimeStep () {
	return timeStep;
}

void Simulador::modelarMundo(Modelo::Mundo* mundo) {
	m_mundo = new b2World(b2Vec2(0,simulador::Constantes::Instancia()->gravedad));
	modelarCuerpos(mundo);
//	m_mundo->SetContactListener(new ContactListener(m_mundo));
	modelarContactos();
}

void Simulador::modelarCuerpos(Modelo::Mundo* mundo) {
	//Sogas y correas.
	std::list<Modelo::EntidadWrapper> uniones;
	for (Modelo::EntidadWrapper ent : *mundo) {
		simulador::Cuerpo* n_cuerpo = nullptr;
		switch (ent.clase()) {
			case Modelo::TipoElemento::PelotaBasquet :
				n_cuerpo = new PelotaBasquet(m_mundo, ent);
				break;
			case Modelo::TipoElemento::PelotaBowling :
				n_cuerpo = new PelotaBowling(m_mundo, ent);
				break;
			case Modelo::TipoElemento::Globo :
				n_cuerpo = new Globo(m_mundo, ent);
				break;
			case Modelo::TipoElemento::Plataforma :
				n_cuerpo = new Plataforma(m_mundo, ent);
				break;
			case Modelo::TipoElemento::Balancin :
				n_cuerpo = new Balancin(m_mundo, ent);
				break;
			case Modelo::TipoElemento::Soga :
				uniones.push_back(ent);
				break;
			case Modelo::TipoElemento::Motor :
				n_cuerpo = new Motor(m_mundo, ent);
				break;
			case Modelo::TipoElemento::Correa :
				uniones.push_back(ent);
				break;
			case Modelo::TipoElemento::Engranaje :
				n_cuerpo = new Engranaje(ent.centro(), m_mundo, ent.angulo(), ent.radio(), true, false, ent);
				break;
			case Modelo::TipoElemento::CintaTransportadora :
				n_cuerpo = new CintaTransportadora(m_mundo, ent);
				break;
			case Modelo::TipoElemento::Clavo :
				n_cuerpo = new Clavo(m_mundo, ent);
				break;
			case Modelo::TipoElemento::Gancho :
				n_cuerpo = new Gancho(m_mundo,ent);
				break;
			case Modelo::TipoElemento::Yunque :
				n_cuerpo = new Yunque(m_mundo, ent);
				break;
			case Modelo::TipoElemento::Huevo :
				n_cuerpo = new Huevo(m_mundo, ent);
				break;
			case Modelo::TipoElemento::Canio :
				n_cuerpo = new Canio(m_mundo, ent);
				break;
			case Modelo::TipoElemento::Codo :
				n_cuerpo = new Codo(m_mundo, ent);
				break;
			case Modelo::TipoElemento::Domino :
				n_cuerpo = new Domino(m_mundo, ent);
				break;
			case Modelo::TipoElemento::Tijera :
				n_cuerpo = new Tijera(m_mundo, ent);
				break;
			case Modelo::TipoElemento::PaletaFlipper :
				n_cuerpo = new PaletaFlipper(m_mundo, ent);
				break;
			case Modelo::TipoElemento::Polea :
				//Creo una polea sin nada conectado.
				n_cuerpo = new Polea(m_mundo, ent);
				uniones.push_back(ent);
				break;
			case Modelo::TipoElemento::Vela :
				n_cuerpo = new Vela(m_mundo, ent);
				break;
			case Modelo::TipoElemento::MotorRaton :
				n_cuerpo = new MotorRaton(m_mundo, ent);
				break;
			case Modelo::TipoElemento::Queso :
				n_cuerpo = new Queso(m_mundo, ent);
				break;
			case Modelo::TipoElemento::Carrito :
				n_cuerpo = new Carrito(m_mundo, ent);
				break;
			case Modelo::TipoElemento::Canasto :
				n_cuerpo = new Canasto(m_mundo, ent);
				break;
		}
		if(n_cuerpo!=nullptr){
			cuerpos.push_back(n_cuerpo);
		}
	}
	if(!uniones.empty()) modelarContactosADistancia(uniones);
}

void Simulador::modelarContactosADistancia(std::list<Modelo::EntidadWrapper> uniones){
	for (auto& entidadUnion : uniones) {
		Cuerpo* bodyA = buscarCuerpo(entidadUnion.entidadExtremoA());
		Cuerpo* bodyB = buscarCuerpo(entidadUnion.entidadExtremoB());
		if (entidadUnion.clase() == Modelo::TipoElemento::Soga) {
			//DEBO CONSTATAR QUE NO ESTÉ UNIDA A UNA POLEA
			if ((entidadUnion.entidadExtremoA().clase() != Modelo::TipoElemento::Polea &&
					entidadUnion.entidadExtremoB().clase() != Modelo::TipoElemento::Polea)) {
				Cuerpo* soga = new Soga(m_mundo, bodyA->getCuerpo(), bodyB->getCuerpo(),entidadUnion);
				cuerpos.push_back(soga);
			}
		} else if (entidadUnion.clase() == Modelo::TipoElemento::Correa) {
			Cuerpo* correa = new Correa(m_mundo, bodyA, bodyB, Constantes::Instancia()->ratioGiroEngranajes, entidadUnion);
			cuerpos.push_back(correa);
			modelarCuerposRotativos(entidadUnion);
		} else if (entidadUnion.clase() == Modelo::TipoElemento::Polea) {
			modelarPolea(entidadUnion);
		}
	}
}

//Busca en la lista de nuestros cuerpos, cuál corresponde a Entidad.
Cuerpo* Simulador::buscarCuerpo(Modelo::EntidadWrapper entidad){
	std::list<Cuerpo*>::iterator iterator;
	for(iterator = cuerpos.begin();iterator != cuerpos.end(); ++iterator) {
		Cuerpo* cuerpo = *iterator;
		if (entidad == cuerpo->entidad) {
			return cuerpo;
		}
	}
	return nullptr;
}

void Simulador::modelarContactos() {
	//recorro todos los contactos que existen en el m_mundo

	for(b2Contact* contact = m_mundo->GetContactList(); contact; contact = contact->GetNext()){

		void* data1 = contact->GetFixtureA()->GetBody()->GetUserData();
		void* data2 = contact->GetFixtureB()->GetBody()->GetUserData();

		if (data1 && data2){
			Cuerpo* body1 = static_cast<Cuerpo*> (data1);
			Cuerpo* body2 = static_cast<Cuerpo*> (data2);

			if(contact->IsTouching()){
				body1->tocarse(body2, m_mundo);
			}

		}
	}
}

void Simulador::modelarCuerpoRotativoCinta(Modelo::EntidadWrapper entidad){
	using Modelo::TipoElemento;

	Modelo::EntidadWrapper entidadA = entidad.entidadExtremoA();
	Modelo::EntidadWrapper entidadB = entidad.entidadExtremoB();

	Cuerpo* bodyA = buscarCuerpo(entidadA);
	Cuerpo* bodyB = buscarCuerpo(entidadB);

	if (entidadB.clase() == TipoElemento::CintaTransportadora && entidadA.esCorreable()) {
		CintaTransportadora* cinta = static_cast<CintaTransportadora*>(bodyB);
		cinta->setSentidoSegunCuerpoRotativo(static_cast<CuerpoRotativo*>(bodyA));
	}

	if (entidadA.clase() == TipoElemento::CintaTransportadora && entidadB.esCorreable()) {
		CintaTransportadora* cinta = static_cast<CintaTransportadora*>(bodyA);
		cinta->setSentidoSegunCuerpoRotativo(static_cast<CuerpoRotativo*>(bodyB));
	}

}

void Simulador::modelarCuerposRotativos(Modelo::EntidadWrapper entidad){
	using Modelo::TipoElemento;

	Modelo::EntidadWrapper entidadA = entidad.entidadExtremoA();
	Modelo::EntidadWrapper entidadB = entidad.entidadExtremoB();

	Cuerpo* bodyA = buscarCuerpo(entidadA);
	Cuerpo* bodyB = buscarCuerpo(entidadB);

	if (entidadA.clase() == TipoElemento::CintaTransportadora ||
	    entidadB.clase() == TipoElemento::CintaTransportadora) {
		modelarCuerpoRotativoCinta(entidad);
	}

	if ((entidadA.clase() == TipoElemento::Motor || entidadA.clase() == TipoElemento::MotorRaton)
			&& entidadB.clase() == TipoElemento::Engranaje) {
		Engranaje* engranaje = (Engranaje*) bodyB;
		engranaje->setSentidoSegunCuerpoRotativo((CuerpoRotativo*) bodyA);
	}

	if ((entidadB.clase() == TipoElemento::Motor || entidadB.clase() == TipoElemento::MotorRaton)
			&& entidadA.clase() == TipoElemento::Engranaje) {
		Engranaje* engranaje = (Engranaje*) bodyA;
		engranaje->setSentidoSegunCuerpoRotativo((CuerpoRotativo*) bodyB);
	}
}

void Simulador::modelarPolea(Modelo::EntidadWrapper entidad) {

	Cuerpo* polea = buscarCuerpo(entidad);
	Polea* poleaCast = static_cast<Polea*> (polea);

	std::list<Modelo::EntidadWrapper> sogasAtadas = entidad.elemPuenteAtado();
	//Es una polea fea y corrupta
	if (sogasAtadas.size() == 1) {
		if ((poleaCast->soga1).valido()) {
			Soga* sogaIntermedia1 = new Soga(m_mundo, buscarCuerpo(poleaCast->soga1.entidadExtremoA())->getCuerpo(),
				 buscarCuerpo(poleaCast->soga1.entidadExtremoB())->getCuerpo(), poleaCast->soga1, 100);
			cuerpos.push_back(sogaIntermedia1);
		} else if ((poleaCast->soga2).valido()){
			Soga* sogaIntermedia2 = new Soga(m_mundo,  buscarCuerpo(poleaCast->soga2.entidadExtremoA())->getCuerpo(),
				 buscarCuerpo(poleaCast->soga2.entidadExtremoB())->getCuerpo(), poleaCast->soga2, 100);
			cuerpos.push_back(sogaIntermedia2);
		}
	} else if (sogasAtadas.size() == 2) {
		if(!buscarCuerpo(poleaCast->soga1)) {
			Soga* sogaIntermedia1 = new Soga(m_mundo, buscarCuerpo(poleaCast->soga1.entidadExtremoA())->getCuerpo(),
				 buscarCuerpo(poleaCast->soga1.entidadExtremoB())->getCuerpo(), poleaCast->soga1, 100);
			cuerpos.push_back(sogaIntermedia1);
		}

		if(!buscarCuerpo(poleaCast->soga2)) {
			Soga* sogaIntermedia2 = new Soga(m_mundo,  buscarCuerpo(poleaCast->soga2.entidadExtremoA())->getCuerpo(),
				 buscarCuerpo(poleaCast->soga2.entidadExtremoB())->getCuerpo(), poleaCast->soga2, 100);
			cuerpos.push_back(sogaIntermedia2);
		}

		poleaCast->conectar();

	}
}

Simulador::~Simulador() {
	for(b2Joint* joint = m_mundo->GetJointList(); joint; joint = joint->GetNext()){
		this->m_mundo->DestroyJoint(joint);
	}

	std::list<Cuerpo*>::const_iterator iterator;
	for(iterator = cuerpos.begin(); iterator != cuerpos.end(); ++iterator){
		delete *iterator;
	}

	delete m_mundo;
}

} /* namespace simulador */
