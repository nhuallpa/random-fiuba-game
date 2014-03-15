/*
 * Polea.cpp
 *
 *  Created on: Nov 2, 2013
 *      Author: lucia
 */

#include "Polea.h"
#include "Soga.h"
#include <set>
#include <iostream>

namespace simulador {

Polea::Polea(b2World* mundo, Modelo::EntidadWrapper entidad)
	: soga1()
	, soga2()
	, pJoint(nullptr)
	, desatada(true)
	, corrupta(false)
{
	/* Polea se modela con un circulo con dos "sogas" (pulleyJoint).
	 *                ___
	 *               /   \
	 *            p1|__.__|p2
	 *               \___/
	 *              |     |
	 *              |     |
	 *              |     |
	 *           p3 C1    C2 p4
	 * Siendo p1 y p2 groundAnchors, p3 y p4 localAnchors y C1 y C2 los cuerpos colgantes.
	 * Los aparejos son una ilusión óptica, funciona poniendo los ground anchors en
	 * cada extremo del aparejo.
	 */


	//Primero se crea la polea desatada.
	this->m_mundo = mundo;
	this->entidad = entidad;
	cuerpo = crearCuerpo(m_mundo);
	b2Body* soporte = crearSoporte(cuerpo);
	JointMaker::crearRevoluteJoint(m_mundo, soporte, cuerpo, false, 0, 0);

	std::list<Modelo::EntidadWrapper> sogasAtadas = entidad.elemPuenteAtado();
	std::list<Modelo::EntidadWrapper>::iterator it;
	if (sogasAtadas.size() == 2) {
		it = sogasAtadas.begin();
		soga1 = *it;
		++it;
		soga2 = *it;
	} else if (sogasAtadas.size() == 1) {
		it = sogasAtadas.begin();
		soga1 = *it;
		corrupta = true;
	}

	cuerpo->SetUserData(this);
}


void Polea::vivir() {
	if (!soga1.valido() || !soga2.valido()) {
		desatada = true;
	}

	if(!desatada) {
		std::pair<Modelo::EntidadWrapper, Modelo::EntidadWrapper> sogasFinales = this->buscarSogasFinales();
		Modelo::EntidadWrapper sogaFinal1 = sogasFinales.first;
		Modelo::EntidadWrapper sogaFinal2 = sogasFinales.second;

		if (sogaFinal1.entidadExtremoA().clase() == Modelo::TipoElemento::Polea) {
			sogaFinal1.puntoDeLigaduraEntidadB() = pJoint->GetAnchorA();
		} else {
			sogaFinal1.puntoDeLigaduraEntidadA() = pJoint->GetAnchorA();
		}
		sogaFinal1.regenerar();

		if (sogaFinal2.entidadExtremoA().clase() == Modelo::TipoElemento::Polea) {
			sogaFinal2.puntoDeLigaduraEntidadB() = pJoint->GetAnchorB();
		} else {
			sogaFinal2.puntoDeLigaduraEntidadA() = pJoint->GetAnchorB();
		}
		sogaFinal2.regenerar();
	}
	entidad.angulo() = cuerpo->GetAngle()*Constantes::Instancia()->RADTODEG;
}

b2Body* Polea::crearCuerpo(b2World* mundo) {
	b2BodyDef myBodyDef;
	myBodyDef.type = b2_staticBody;
	myBodyDef.position.Set(entidad.centro().x, entidad.centro().y);
	b2Body* poleaCuerpo = m_mundo->CreateBody(&myBodyDef);
	b2CircleShape circleShape;
	circleShape.m_p.Set(0, 0);
	circleShape.m_radius = entidad.radio();
	b2FixtureDef myFixtureDef;
	myFixtureDef.shape = &circleShape;
	myFixtureDef.density = Constantes::Instancia()->densidadPolea;
	myFixtureDef.restitution = Constantes::Instancia()->coeficienteRestitucionPolea;
	poleaCuerpo->CreateFixture(&myFixtureDef);
	return poleaCuerpo;
}

b2Body* Polea::crearSoporte(b2Body* cuerpo){
	b2Body* body;
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(cuerpo->GetPosition().x, cuerpo->GetPosition().y);
	b2FixtureDef fixtureDef;
	b2CircleShape circleShape2;
	circleShape2.m_radius = 0;
	fixtureDef.shape = &circleShape2;
	body = m_mundo->CreateBody( &bodyDef );
	body->CreateFixture( &fixtureDef );
	return body;
}


std::list<Modelo::EntidadWrapper> Polea::getAparejo() {
	//Return
	std::list<Modelo::EntidadWrapper> entidades;
	//actuales
	//Tengo que empezar a iterar por una polea.
	Modelo::EntidadWrapper entidadActual;
	if ((soga1.entidadExtremoA() == entidad))
		entidadActual = soga1.entidadExtremoA();
	else
		entidadActual = soga1.entidadExtremoB();

	Modelo::EntidadWrapper sogaAct = soga1;
	Modelo::EntidadWrapper sogaAct1;
	Modelo::EntidadWrapper sogaAct2;

	//Se colectan los que ya revisé
	std::set<Modelo::EntidadWrapper> entidadesConocidas;
	entidadesConocidas.insert(entidadActual);
	entidadesConocidas.insert(sogaAct);

	//Se corrompe si una de las poleas no está atada de los dos lados
	bool ultima = false;

	while ((entidadActual.clase() == Modelo::TipoElemento::Polea) && !corrupta) {
		std::list<Modelo::EntidadWrapper> sogasAtadas = entidadActual.elemPuenteAtado();
		std::list<Modelo::EntidadWrapper>::iterator it;
		if (sogasAtadas.size() == 2) {
			it = sogasAtadas.begin();
			sogaAct1 = *it;
			++it;
			sogaAct2 = *it;
		} else {
			corrupta = true;
		}
		//Compruebo que la soga1 no la haya revisado.
		if ((entidadesConocidas.find(sogaAct1)== entidadesConocidas.end())) {
			sogaAct = sogaAct1;
			entidadesConocidas.insert(sogaAct);
			entidades.push_back(sogaAct);
		} else if((entidadesConocidas.find(sogaAct2)== entidadesConocidas.end())) {
			sogaAct = sogaAct2;
			entidadesConocidas.insert(sogaAct);
			entidades.push_back(sogaAct);
		} else {
			//ya conozco las dos sogas
			corrupta = true;
		}

		if (entidadesConocidas.find(sogaAct.entidadExtremoA())== entidadesConocidas.end() ) {
			entidadActual = sogaAct.entidadExtremoA();
			entidadesConocidas.insert(entidadActual);
			entidades.push_back(entidadActual);
		} else if (entidadesConocidas.find(sogaAct.entidadExtremoB())== entidadesConocidas.end() ) {
			entidadActual = sogaAct.entidadExtremoB();
			entidadesConocidas.insert(entidadActual);
			entidades.push_back(entidadActual);
		} else {
			//Recorri y no encontré ningún objeto colgando
			corrupta = true;
		}

		if ((entidadActual.clase() != Modelo::TipoElemento::Polea) &&  !ultima) {
			ultima = true;
			//Llegué a un extremo, así que reseteo y empiezo a buscar la lista final.
			entidadesConocidas.clear();
			entidades.clear();
			//En sogaAct me queda la soga que ata al objeto que está en un extremo
			if ((sogaAct.entidadExtremoA().clase() == Modelo::TipoElemento::Polea))
				entidadActual = sogaAct.entidadExtremoA();
			else
				entidadActual = sogaAct.entidadExtremoB();
			entidadesConocidas.insert(sogaAct);
			entidadesConocidas.insert(entidadActual);
			entidades.push_back(sogaAct);
			entidades.push_back(entidadActual);
		}

	}
	if (corrupta) {
		entidades.clear();
		return entidades;
	}
	entidades.pop_back();
	return entidades;

}

void Polea::borrarPulley(){
	if (pJoint != nullptr) {
		m_mundo->DestroyJoint(pJoint);
		pJoint = nullptr;
		desatada = true;
	}
}

void Polea::romperAparejo() {
	if (corrupta) {
		if(soga1.valido()) {
			Soga* sogaCuerpo = static_cast<Soga*> (buscarCuerpoEnMundo(soga1));
			sogaCuerpo->cortarSoga();
			sogaCuerpo->vivir();
		}
		if(soga2.valido()) {
			Soga* sogaCuerpo = static_cast<Soga*> (buscarCuerpoEnMundo(soga2));
			sogaCuerpo->cortarSoga();
			sogaCuerpo->vivir();
		}
		return;
	}
	if (desatada)
		return;
	std::list<Modelo::EntidadWrapper> lista = this->getAparejo();
	std::list<Modelo::EntidadWrapper>::iterator iterator;
	std::list<Soga*> sogasACortar;
	for (iterator = lista.begin(); iterator != lista.end(); iterator++) {
		Modelo::EntidadWrapper entidad = *iterator;
		if (entidad.clase() == Modelo::TipoElemento::Soga) {
			if (entidad.valido()) {
				Soga* sogaCuerpo = static_cast<Soga*> (buscarCuerpoEnMundo(entidad));
				sogasACortar.push_back(sogaCuerpo);
			}
		}
		if (entidad.clase() == Modelo::TipoElemento::Polea) {
			Polea* poleaSig = static_cast<Polea*> (buscarCuerpoEnMundo(entidad));
			poleaSig->borrarPulley();
		}
	}
	std::list<Soga*>::iterator itSogas;
	for(itSogas = sogasACortar.begin(); itSogas != sogasACortar.end(); ++itSogas) {
		Soga* s = *itSogas;
		s->cortarSoga();
		s->vivir();
	}
}



std::pair<Modelo::EntidadWrapper, Modelo::EntidadWrapper> Polea::buscarSogasFinales() {
	std::pair<Modelo::EntidadWrapper, Modelo::EntidadWrapper> sogasFinales;
	std::list<Modelo::EntidadWrapper> lista = this->getAparejo();
	if (lista.size() > 2) {
		sogasFinales.first = lista.front();
		sogasFinales.second = lista.back();
	} else {
		Modelo::EntidadWrapper e1, e2;
		sogasFinales = std::make_pair(e1,e2);
	}
	return sogasFinales;
}

Modelo::EntidadWrapper Polea::getEntidadSogueada(Modelo::EntidadWrapper soga){
	if (soga.entidadExtremoA().clase() != Modelo::TipoElemento::Polea) {
		return soga.entidadExtremoA();
	} else if (soga.entidadExtremoB().clase() != Modelo::TipoElemento::Polea) {
		return soga.entidadExtremoB();
	}
	return Modelo::EntidadWrapper();
}

void Polea::conectar() {

	b2Vec2 puntoLocalA;
	b2Vec2 puntoLocalB;
	b2Vec2 groundAnchorA;
	b2Vec2 groundAnchorB;

	std::pair<Modelo::EntidadWrapper, Modelo::EntidadWrapper> sogasFinales = this->buscarSogasFinales();
	Modelo::EntidadWrapper sogaFinal1 = sogasFinales.first;
	Modelo::EntidadWrapper sogaFinal2 = sogasFinales.second;

	if (corrupta)
		return;
	if (!sogaFinal1.valido() || !sogaFinal2.valido()) {
		return;
	}

	Modelo::EntidadWrapper ObjetoFinalSogaFinal1 = this->getEntidadSogueada(sogaFinal1);
	Modelo::EntidadWrapper ObjetoFinalSogaFinal2 = this->getEntidadSogueada(sogaFinal2);

	if (ObjetoFinalSogaFinal1 == ObjetoFinalSogaFinal2) {
		corrupta = true;
		return;
	}

	//Arreglo esto para que globo atado a yunque no traiga problemas
	if (ObjetoFinalSogaFinal1.clase() == Modelo::TipoElemento::Globo && ObjetoFinalSogaFinal2.clase() == Modelo::TipoElemento::Yunque) {
		Cuerpo* globo = buscarCuerpoEnMundo(ObjetoFinalSogaFinal1);
		globo->getCuerpo()->GetFixtureList()->SetDensity(10);
		globo->getCuerpo()->ResetMassData();
	}
	if (ObjetoFinalSogaFinal2.clase() == Modelo::TipoElemento::Globo && ObjetoFinalSogaFinal1.clase() == Modelo::TipoElemento::Yunque) {
		Cuerpo* globo = buscarCuerpoEnMundo(ObjetoFinalSogaFinal2);
		globo->getCuerpo()->GetFixtureList()->SetDensity(10);
		globo->getCuerpo()->ResetMassData();
	}

	if (sogaFinal1.entidadExtremoA().clase() == Modelo::TipoElemento::Polea) {
		 puntoLocalA = b2Vec2(sogaFinal1.puntoDeLigaduraEntidadB())-ObjetoFinalSogaFinal1.centro();
		 groundAnchorA = b2Vec2(sogaFinal1.puntoDeLigaduraEntidadA());
	} else {
		puntoLocalA = b2Vec2(sogaFinal1.puntoDeLigaduraEntidadA()) - ObjetoFinalSogaFinal1.centro();
		groundAnchorA = b2Vec2(sogaFinal1.puntoDeLigaduraEntidadB());

	}
	if (sogaFinal2.entidadExtremoA().clase() == Modelo::TipoElemento::Polea) {
		puntoLocalB = b2Vec2(sogaFinal2.puntoDeLigaduraEntidadB()) - ObjetoFinalSogaFinal2.centro();
		groundAnchorB = b2Vec2(sogaFinal2.puntoDeLigaduraEntidadA());

	} else {
		puntoLocalB = b2Vec2(sogaFinal2.puntoDeLigaduraEntidadA()) - ObjetoFinalSogaFinal2.centro();
		groundAnchorB = b2Vec2(sogaFinal2.puntoDeLigaduraEntidadB());

	}

	b2Vec2 localAnchorA = Vec2(1,-1) * Vec2(puntoLocalA).rotar(ObjetoFinalSogaFinal1.angulo());
	b2Vec2 localAnchorB = Vec2(1,-1) * Vec2(puntoLocalB).rotar(ObjetoFinalSogaFinal2.angulo());

	Vec2 globalAnchorA = b2Vec2(ObjetoFinalSogaFinal1.centro()) + puntoLocalA;
	Vec2 globalAnchorB = b2Vec2(ObjetoFinalSogaFinal2.centro()) + puntoLocalB;
	float maxLengthA = Vec2(groundAnchorA).distancia(globalAnchorA);
	float maxLengthB = Vec2(groundAnchorB).distancia(globalAnchorB);

	desatada = false;
	Cuerpo* cuerpo1 = buscarCuerpoEnMundo(ObjetoFinalSogaFinal1);
	Cuerpo* cuerpo2 = buscarCuerpoEnMundo(ObjetoFinalSogaFinal2);

	this->pJoint = JointMaker::crearJointPolea(cuerpo1->getCuerpo(), cuerpo2->getCuerpo(), groundAnchorA, groundAnchorB, localAnchorA, localAnchorB, 1, maxLengthA,
			maxLengthB, m_mundo);
}

bool Polea::estaCorrupta() const {
	return corrupta;
}

Cuerpo* Polea::buscarCuerpoEnMundo(Modelo::EntidadWrapper entidad) {

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
	return nullptr;
}

Polea::~Polea() {
}

b2Vec2 Polea::getReactionForce(Cuerpo* afectado) {
	Vec2 mayor(0,0);
	if (corrupta)
		return mayor;
	b2Joint* pulleyValido;
	//Busco el pulley con la mayor reaction force del aparejo.
	std::list<Modelo::EntidadWrapper> lista = this->getAparejo();
	std::list<Modelo::EntidadWrapper>::iterator iterator;
	for (iterator = lista.begin(); iterator != lista.end(); iterator++) {
		Modelo::EntidadWrapper entidad = *iterator;
		if (entidad.clase() == Modelo::TipoElemento::Polea) {
			Polea* poleaSig = static_cast<Polea*> (buscarCuerpoEnMundo(entidad));
			Vec2 actual = Vec2(poleaSig->getPulleyJoint()->GetReactionForce(1/Constantes::Instancia()->iteracionesPorSegundo));
			if (actual.abs() > mayor.abs()){
				mayor = actual;
				pulleyValido = poleaSig->getPulleyJoint();
			}
		}
	}

	b2Vec2 rF(mayor.x, mayor.y);
	int signo = 1;
	if (pulleyValido != nullptr) {
		//gerReactionForce siempre devuelve la fuerza que hace el pulley sobre el body2
		if (pulleyValido->GetBodyB() == afectado->getCuerpo()) {
			signo = 1;
		} else {
			signo = -1;
		}
		float enX = (signo)*mayor.x;
		float enY = (signo)*mayor.y;
		rF = b2Vec2(Vec2(-1,-1)*Vec2(enX,enY));
	}

	return rF;
}

b2Joint* Polea::getPulleyJoint(){
	return pJoint;
}
} /* namespace simulador */
