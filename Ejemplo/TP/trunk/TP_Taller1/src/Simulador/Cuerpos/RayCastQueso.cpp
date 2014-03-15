/*
 * RayCastClosestCallback.cpp
 *
 *  Created on: Nov 28, 2013
 *      Author: lucia
 */

#include "RayCastQueso.h"
#include <iostream>

namespace simulador {

std::set<Modelo::TipoElemento> init()
{
	std::set<Modelo::TipoElemento> tmp;
	tmp.insert(Modelo::TipoElemento::Globo);
	tmp.insert(Modelo::TipoElemento::Gancho);
	tmp.insert(Modelo::TipoElemento::Soga);
	tmp.insert(Modelo::TipoElemento::Clavo);
	return tmp;
 }

std::set<Modelo::TipoElemento> RayCastQueso::transparentes(init());


RayCastQueso::RayCastQueso(Modelo::EntidadWrapper motorRaton)
	: cuerpoChocado(nullptr)
	, m_hit(false)
	, m_point()
	, m_normal()
	, entidadVisora(motorRaton)
{
}

float32 RayCastQueso::ReportFixture(b2Fixture* fixture, const b2Vec2& point,
		const b2Vec2& normal, float32 fraction)
{
	b2Body* body = fixture->GetBody();
	void* userData = body->GetUserData();
	if (userData)
	{
		int32 index = *(int32*)userData;
		void* cdata = body->GetUserData();
		if (cdata) {
			auto entidad = static_cast<Cuerpo*>(cdata)->entidad;
			//Filtra soga
			if (!entidad.valido()) {
				return -1.0f;
			}
			else if(transparentes.find(entidad.clase()) != transparentes.end()) {
				return -1.0f;
			} else if(entidad == entidadVisora) {
				return -1.0f;
			}
//			std::cout << "El raton ve: " << Modelo::tipoElementoToString(entidad.clase()) << std::endl;
		}

		if (index == 0)
		{
			return -1.0f;
		}
	}

	void* data = body->GetUserData();
	if (!data) {
		return -1.0f;
	}
	cuerpoChocado = body;
	return fraction;
}


bool RayCastQueso::veQueso(){
	if (cuerpoChocado != nullptr)
	{
		if(cuerpoChocado->GetUserData() != nullptr){
			auto entidad = static_cast<Cuerpo*>(cuerpoChocado->GetUserData())->entidad;
			if (entidad.valido() && entidad.clase() == Modelo::TipoElemento::Queso) {
				return true;
			} else {
				return false;
			}
		}
	}
	return false;
}

RayCastQueso::~RayCastQueso() {
}
}

