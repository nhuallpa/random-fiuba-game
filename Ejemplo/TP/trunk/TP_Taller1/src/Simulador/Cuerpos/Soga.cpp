/*
 * Soga.cpp
 *
 *  Created on: 04/10/2013
 *      Author: stephanie
 */

#include "Soga.h"

#include "Sonido/Sonido.h"
#include "Simulador/Constantes.h"
#include "Polea.h"
#include <Box2D/Box2D.h>
#include <cmath>

namespace simulador {

Soga::Soga(b2World* mundo, b2Body* bodyA, b2Body* bodyB, Modelo::EntidadWrapper entidad)
	: bodyA(bodyA)
	, bodyB(bodyB)
	, cuerpoA()
	, cuerpoB()
	, rJoint(nullptr)
	, puntoLigaduraA(entidad.puntoDeLigaduraEntidadA())
	, puntoLigaduraB(entidad.puntoDeLigaduraEntidadB())
	, existeSoga(true)
	, tiempoQuemandose(0)
{
	this->entidad = entidad;
	b2Vec2 puntoLocalA = b2Vec2(entidad.puntoDeLigaduraEntidadA()) - bodyA->GetWorldCenter();
	b2Vec2 puntoLocalB = b2Vec2(entidad.puntoDeLigaduraEntidadB()) - bodyB->GetWorldCenter();
	this->unir(mundo, puntoLocalA, puntoLocalB);
	this->cuerpoA = static_cast<Cuerpo*> (bodyA->GetUserData());
	this->cuerpoB = static_cast<Cuerpo*> (bodyB->GetUserData());

	Modelo::EntidadWrapper eA = cuerpoA->entidad;
	Modelo::EntidadWrapper eB = cuerpoB->entidad;
	//Arreglo esto para que globo atado a yunque no traiga problemas
	if (eA.clase() == Modelo::TipoElemento::Globo && eB.clase() == Modelo::TipoElemento::Yunque) {
		cuerpoA->getCuerpo()->GetFixtureList()->SetDensity(25);
		cuerpoA->getCuerpo()->ResetMassData();
	}
	if (eB.clase() == Modelo::TipoElemento::Globo && eA.clase() == Modelo::TipoElemento::Yunque) {
		cuerpoB->getCuerpo()->GetFixtureList()->SetDensity(25);
		cuerpoB->getCuerpo()->ResetMassData();
	}

	this->m_mundo = mundo;
	this->cuerpo = crearCuerpo();
	this->cuerpo->SetUserData(this);
}

Soga::Soga(b2World* mundo, b2Body* bodyA, b2Body* bodyB, Modelo::EntidadWrapper entidad, float maxlength)
	: bodyA(bodyA)
	, bodyB(bodyB)
	, cuerpoA(static_cast<Cuerpo*> (bodyA->GetUserData()))
	, cuerpoB(static_cast<Cuerpo*> (bodyB->GetUserData()))
	, rJoint(nullptr)
	, puntoLigaduraA(entidad.puntoDeLigaduraEntidadA())
	, puntoLigaduraB(entidad.puntoDeLigaduraEntidadB())
	, existeSoga(true)
	, tiempoQuemandose(0)
{
	this->entidad = entidad;
	b2Vec2 puntoLocalA = b2Vec2(entidad.puntoDeLigaduraEntidadA()) - bodyA->GetWorldCenter();
	b2Vec2 puntoLocalB = b2Vec2(entidad.puntoDeLigaduraEntidadB()) - bodyB->GetWorldCenter();
	this->unir(mundo, puntoLocalA, puntoLocalB, maxlength);
	this->m_mundo = mundo;
	this->cuerpo = crearCuerpo();
	this->cuerpo->SetUserData(this);
}

Soga::~Soga() {
}

void Soga::vivir(){
	if (existeSoga && (entidad.valido())){
		//TODO: Si la soga se estira mucho, la corto
		entidad.puntoDeLigaduraEntidadA() = rJoint->GetAnchorA();
		entidad.puntoDeLigaduraEntidadB() = rJoint->GetAnchorB();
		entidad.regenerar();
		modelarContacto();

	}else{
		if (entidad.valido()){
			entidad.borrar();
		}
	}
	actualizarCuerpo();
}

void Soga::unir(b2World* mundo, b2Vec2 puntoA, b2Vec2 puntoB){
	b2RopeJointDef j;
	j.collideConnected = true;
	j.bodyA = this->bodyA;
	j.bodyB = this->bodyB;
	/* El sistema local y los puntos ya vienen rotados, por lo que necesito
	 * cancelar alguna de las dos rotaciones */
	auto cte = Constantes::Instancia();
	j.localAnchorA = Vec2(1,-1) * Vec2(puntoA).rotar(bodyA->GetAngle() * cte->RADTODEG);
	j.localAnchorB = Vec2(1,-1) * Vec2(puntoB).rotar(bodyB->GetAngle() * cte->RADTODEG);
	Vec2 globalAnchorA = bodyA->GetPosition() + puntoA;
	Vec2 globalAnchorB = bodyB->GetPosition() + puntoB;
	j.maxLength = globalAnchorA.distancia(globalAnchorB);
	rJoint = (b2RopeJoint*) mundo->CreateJoint(&j);
}

void Soga::unir(b2World* mundo, b2Vec2 puntoA, b2Vec2 puntoB, float maxlength){
	b2RopeJointDef j;
	j.collideConnected = true;
	j.bodyA = this->bodyA;
	j.bodyB = this->bodyB;
	/* El sistema local y los puntos ya vienen rotados, por lo que necesito
	 * cancelar alguna de las dos rotaciones */
	auto cte = Constantes::Instancia();
	j.localAnchorA = Vec2(1,-1) * Vec2(puntoA).rotar(bodyA->GetAngle() * cte->RADTODEG);
	j.localAnchorB = Vec2(1,-1) * Vec2(puntoB).rotar(bodyB->GetAngle() * cte->RADTODEG);
	j.maxLength = maxlength;
	rJoint = (b2RopeJoint*) mundo->CreateJoint(&j);
}

b2Body* Soga::crearCuerpo(){
	if (!existeSoga) {
		//TODO: que pasa aca?
		return nullptr;
	}

	b2EdgeShape edgeShape;
	b2Vec2 puntoA;
	b2Vec2 puntoB;
	b2Vec2 anchorA = rJoint->GetAnchorA();
	b2Vec2 anchorB = rJoint->GetAnchorB();

	float xA, xB, yA, yB = 0;

	if (anchorA.y > anchorB.y){
		yA = -0.3;
		yB = 0.3;
		if (abs(anchorA.x - anchorB.x) > 0.2){
			if (anchorA.x > anchorB.x){
				xA = -0.2;
				xB = 0.2;
			}
			if (anchorA.x < anchorB.x){
				xA = 0.2;
				xB = -0.2;
			}
		}else{
			xA = 0;
			xB = 0;
		}

		puntoA = b2Vec2(anchorA + b2Vec2(xA,yA));
		puntoB = b2Vec2(anchorB + b2Vec2(xB,yB));
	}
	if (anchorA.y < anchorB.y){
		yA = 0.3;
		yB = -0.3;
		if (abs(anchorA.x - anchorB.x) > 0.2){
			if (anchorA.x > anchorB.x){
				xA = -0.2;
				xB = 0.2;
			}
			if (anchorA.x < anchorB.x){
				xA = 0.2;
				xB = -0.2;
			}
		}else{
			xA = 0;
			xB = 0;
		}
		puntoA = b2Vec2(anchorA + b2Vec2(xA, yA));
		puntoB = b2Vec2(anchorB + b2Vec2(xB, yB));
	}
	edgeShape.Set(puntoA, puntoB);
	b2BodyDef bodyDef;
	b2Body* body = m_mundo->CreateBody(&bodyDef);

	body->CreateFixture(&edgeShape,0.0f);
	b2Filter filter;
	filter.categoryBits = 0x0001;
	body->GetFixtureList()->SetFilterData(filter);
	body->GetFixtureList()->SetSensor(true);
	return body;
}

void Soga::modelarContacto(){
	for (b2ContactEdge* ce = cuerpo->GetContactList(); ce; ce = ce->next){
		b2Contact* c = ce->contact;
		b2Fixture* a = c->GetFixtureA();
		b2Fixture* b = c->GetFixtureB();

		if (c->IsTouching()){
			void* data = ce->other->GetUserData();
			if (data){
				Cuerpo* otroCuerpo = static_cast<Cuerpo*> (data);

				// Caso cortar soga con vela
				if (otroCuerpo->entidad.clase() == Modelo::TipoElemento::Vela) {
					if (a->GetFilterData().categoryBits == 0x0002 || b->GetFilterData().categoryBits == 0x0002) {
						if (tiempoQuemandose >= TIEMPO_DE_QUEMADO_NECESARIO) {
							Sonido::Instancia()->playSound(entidad);
							//Si soga tiene atada alguna polea tengo que llamar al romperAparejo.
							if (entidad.entidadExtremoA().clase() == Modelo::TipoElemento::Polea) {
								Polea* polea = static_cast<Polea*> (cuerpoA);
								polea->romperAparejo();
							} else if (entidad.entidadExtremoB().clase() == Modelo::TipoElemento::Polea) {
								Polea* polea = static_cast<Polea*> (cuerpoB);
								polea->romperAparejo();
							} else {
								cortarSoga();
							}
							break;
						}
						else {
							tiempoQuemandose++;
						}
					}
				}

			}
		}
	}
}

void Soga::cortarSoga(){
	existeSoga = false;
	m_mundo->DestroyJoint(rJoint);
//	cuerpo->SetActive(false);
	cuerpo->SetAwake(false);
	//Parche, cuando se destruye el cuerpo
	//para que no se queje box, crea un edge muy chico como
	//cuerpo y manda el cuerpo lejos para que no interfiera.
	m_mundo->DestroyBody(cuerpo);
	cuerpo = JointMaker::crearEdge(b2Vec2(0,0), b2Vec2(0,0.1), m_mundo);
	cuerpo->SetTransform(b2Vec2(-1000, -1000),0);

}

void Soga::actualizarCuerpo(){
	if (existeSoga){
		m_mundo->DestroyBody(cuerpo);
		this->cuerpo = crearCuerpo();
		cuerpo->SetUserData(this);
	}
}

b2RopeJoint* Soga::getRopeJoint(){
	if (existeSoga)
		return rJoint;
	return nullptr;
}

} /* namespace simulador */
