/*
 * Globo.cpp
 *
 *  Created on: Oct 4, 2013
 *      Author: lucia
 */

#include "Globo.h"
#include "Soga.h"
#include "Polea.h"

#include "Simulador/Constantes.h"
#include "Sonido/Sonido.h"
#include <Box2D/Box2D.h>

namespace simulador {

Globo::Globo(b2World* mundo, Modelo::EntidadWrapper entidad)
	: Pelota(Constantes::Instancia()->coeficienteRestitucionGlobo,
	         Constantes::Instancia()->densidadGlobo, mundo, entidad)
	, exploto(false)
{
	this->posicionInicial = entidad.centro();
	//cambio el userData
	this->cuerpo->SetUserData(this);
	this->entidad.estadoNormal() = true;
}

void Globo::vivir(){
	if (!this->exploto){
		Constantes* cte = Constantes::Instancia();
		float volumen = this->cuerpo->GetMass() / cte->densidadGlobo;
		float fuerzaFlotacion = volumen * cte->densidadAire * cte->gravedad;
		if (!this->entidad.accionar() && entidad.estadoNormal()) {
			//Le doy una fuerza que corresponderia si hubiera aire
			this->cuerpo->ApplyForceToCenter(b2Vec2(0, -fuerzaFlotacion));
		} else {
			this->exploto = true;
			entidad.estadoNormal() = false;
			entidad.accionar() = true;
			Sonido::Instancia()->playSound(entidad);
			b2Fixture* fix = this->cuerpo->GetFixtureList();
			fix->SetDensity(0.0000001);
			fix->SetSensor(true);
			this->cuerpo->ResetMassData();
			std::list<Modelo::EntidadWrapper>::iterator it = entidad.elemPuenteAtado().begin();
			if (entidad.elemPuenteAtado().size() > 0) {
				Modelo::EntidadWrapper soga = *it;
				Soga* sogaCuerpo = static_cast<Soga*> (buscarCuerpoEnMundo(soga));
				if(soga.entidadExtremoA().valido() && soga.entidadExtremoB().valido()){
					if (soga.entidadExtremoA().clase() == Modelo::TipoElemento::Polea) {
						Polea* polea = static_cast<Polea*> (buscarCuerpoEnMundo(soga.entidadExtremoA()));
						polea->romperAparejo();
					} else if (soga.entidadExtremoB().clase() == Modelo::TipoElemento::Polea) {
						Polea* polea = static_cast<Polea*> (buscarCuerpoEnMundo(soga.entidadExtremoB()));
						polea->romperAparejo();
					} else {
						sogaCuerpo->cortarSoga();
					}
				}
			}
		}
	}
	entidad.centro() = cuerpo->GetPosition();
}

Cuerpo* Globo::buscarCuerpoEnMundo(Modelo::EntidadWrapper entidad) {

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

Globo::~Globo() {
}

} /* namespace simulador */
