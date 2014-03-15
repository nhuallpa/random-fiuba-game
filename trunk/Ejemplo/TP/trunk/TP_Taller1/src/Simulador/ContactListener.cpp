/*
 * ContactListener.cpp
 *
 *  Created on: Nov 20, 2013
 *      Author: lucia
 */

#include "ContactListener.h"
#include "Sonido/Sonido.h"
#include "Cuerpo.h"
#include "Cuerpos/Huevo.h"

namespace simulador {

ContactListener::ContactListener() {
}

void ContactListener::BeginContact(b2Contact* contact) {

	if (!contact->IsTouching()) {
		return;
	}

	void* data1 = contact->GetFixtureA()->GetBody()->GetUserData();
	void* data2 = contact->GetFixtureB()->GetBody()->GetUserData();
	if (!data1 || !data2) {
		return;
	}

	auto ca = static_cast<Cuerpo*>(data1);
	auto cb = static_cast<Cuerpo*>(data2);
	auto entidad1 = ca->entidad;
	auto entidad2 = cb->entidad;
	if (!entidad1.valido() || !entidad2.valido()) {
		return;
	}

	auto sonido = Sonido::Instancia();
	if (sonido != nullptr) {
		sonido->playSound(entidad1, entidad2);
	}

	//Globo chocando con clavo revienta el globo
	using Modelo::TipoElemento;
	if ((entidad1.clase() == TipoElemento::Globo && entidad2.clase() == TipoElemento::Clavo) ||
	    (entidad1.clase() == TipoElemento::Clavo && entidad2.clase() == TipoElemento::Globo)) {
		if (contact->GetFixtureA()->GetFilterData().categoryBits == 0x0004 ||
				contact->GetFixtureB()->GetFilterData().categoryBits == 0x0004){
			if (entidad1.clase() == TipoElemento::Globo) {
				entidad1.accionar() = true;
			} else {
				entidad2.accionar() = true;
			}
		}
	}
	if (entidad1.clase() == TipoElemento::Huevo) {
		static_cast<Huevo*>(ca)->modelarContacto(contact);
	} else if(entidad2.clase() == TipoElemento::Huevo) {
		static_cast<Huevo*>(cb)->modelarContacto(contact);
	}
}

void ContactListener::resolverContactosHuevo(b2Contact* contact) {

}

ContactListener::~ContactListener() {
}

} /* namespace simulador */
