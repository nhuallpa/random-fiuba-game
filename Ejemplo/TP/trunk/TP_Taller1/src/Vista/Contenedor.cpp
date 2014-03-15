/*
 * Contenedor.cpp
 *
 *  Created on: Sep 5, 2013
 *      Author: lucia
 */

#include "Contenedor.h"

#include "Log/Suceso.h"
#include "Modelo/Jugador.h"
#include "Utils/iteracion.h"
#include "Utils/make_unique.h"
#include "Utils/Rect.h"
#include "Vista/ClickInfo.h"
#include "Vista/Color.h"
#include "Vista/Imagen.h"
#include "Vista/FiguraVista.h"
#include "Vista/LayoutInfo.h"
#include "Vista/Textura.h"
#include "Vista/Interfases/OrigenDestinoDibujo.h"
#include "Vista/FuentesPosicion/FuentePosicion.h"

#include <utility>

Contenedor::Contenedor(const FuentePosicion& fuente, Dibujable* destino)
	: vista::Elemento(fuente)
	, fondo()
	, apariencia(*destino, fuente.getSuperficie().tam())
	, permitirEliminaciones(false)
	, dirty_(true)
	, elementos()
{
//	setBackground("imagenes/exampleimage.bmp", destino);
}

void Contenedor::addElemento(vista::Elemento* fig, vista::PrioridadDibujo prioridad) {
	elementos[prioridad].push_front(fig);
	dirty_ = true;
}

void Contenedor::regenerar() {
	if (fuente->getSuperficie().tam() != apariencia.tamDibujo()) {
		apariencia = Textura((DestinoDibujo&)apariencia, fuente->getSuperficie().tam());
	}

	apariencia.limpiar();
	if (fondo) {
		fondo->dibujar(apariencia);
	}
	auto listadoElementos = listarElementos();
	for (auto& elemento : invertir_iteracion(listadoElementos)) {
		try {
			elemento->dibujarse(&apariencia);
		} catch (...) {
			this->quitarElemento(elemento);
		}
	}
	dirty_ = false;
}

void Contenedor::dibujarse (DestinoDibujo* destino) {
	if (dirty()) {
		regenerar();
	}
	apariencia.dibujar(*destino, *fuente);
}

bool Contenedor::dirty() {
	if (dirty_) {
		return true;
	}
	for (auto& emt : listarElementos()) {
		if (emt->dirty()) {
			return true;
		}
	}
	return false;
}

Contenedor::~Contenedor() {
	vaciar();
}

void Contenedor::setBackground(std::string filename, Dibujable* destino) {
	fondo = make_unique<Imagen>(filename, destino);
	dirty_ = true;
}

void Contenedor::setBackground(vista::Color color, Dibujable* destino) {
	auto nFondo = make_unique<Textura>(*destino, Vec2(1, 1));
	nFondo->limpiar(color);
	fondo = std::move(nFondo);
	dirty_ = true;
}

void Contenedor::setBackground(std::unique_ptr<OrigenDibujo> nFondo) {
	fondo = std::move(nFondo);
	dirty_ = true;
}

vista::ClickInfo Contenedor::recibirClick(Vec2 posicionMouse) {
	auto elemento = buscar_base(posicionMouse);
	if (elemento != nullptr) {
		Vec2 mouseRelativo = posicionMouse - fuente->getSuperficie().origen();
	    	return elemento->recibirClick(mouseRelativo);
	}
	return vista::ClickInfo();
}

void Contenedor::desplazarHaciaArriba(Vec2 posicionRespectoPadre){
	auto elemento = buscar_base(posicionRespectoPadre);
	if (elemento != nullptr) {
		Vec2 posicion = posicionRespectoPadre - this->fuente->getSuperficie().origen();
		elemento->desplazarHaciaArriba(posicion);
	}
}

void Contenedor::desplazarHaciaAbajo(Vec2 posicionRespectoPadre){
	auto elemento = buscar_base(posicionRespectoPadre);
	if (elemento != nullptr) {
		Vec2 posicion = posicionRespectoPadre - this->fuente->getSuperficie().origen();
		elemento->desplazarHaciaAbajo(posicion);
	}
}

bool Contenedor::aEliminar (Vec2 posicionRespectoPadre){
	auto elemento = buscar_base(posicionRespectoPadre);
	if (elemento != nullptr) {
		Vec2 posicion = posicionRespectoPadre - this->fuente->getSuperficie().origen();
		if (elemento->aEliminar(posicion) && permitirEliminaciones) {
			quitarElemento(elemento);
		}
	}
	return false;
}

bool Contenedor::recibirFigura (const FiguraVista *elemento, Vec2 pos, vista::PrioridadDibujo prioridad){
	Vec2 relativo = pos - fuente->getSuperficie().origen();
	auto objetivo = buscar_base(relativo);
	if (objetivo != nullptr) {
		return objetivo->recibirFigura(elemento, relativo, prioridad);
	}
	return false;
}

bool Contenedor::accionarElementos(FiguraVista* figura, Vec2 pos, Modelo::TipoAccion accion) {

	Vec2 relativo = pos - fuente->getSuperficie().origen();
	for (auto& par : elementos) {
		for (auto& elemento : par.second) {
			if(elemento->accionarElementos(figura, relativo, accion))
				return true;
		}
	}


	return false;
}

bool Contenedor::recibirElementoPuente(FiguraVista *elemento, Vec2 extremoA,
		Vec2 extremoB, vista::PrioridadDibujo prioridad)
{
	Vec2 relativoA = extremoA - fuente->getSuperficie().origen();
	Vec2 relativoB = extremoB - fuente->getSuperficie().origen();
	auto objA = buscar_base(relativoA);
	if (objA == nullptr) {
		return false;
	}
	auto objB = buscar_base(relativoB);
	if (objB != objA) {
		return false;
	}
	return objA->recibirElementoPuente(elemento, relativoA, relativoB, prioridad);
}

std::pair<bool,Rect> Contenedor::superficieAbsoluta (Elemento *elemento) {
	if (this == elemento) {
		return std::make_pair(true, getSuperficie());
	} else {
		for (auto& emt : listarElementos()) {
			auto par = emt->superficieAbsoluta(elemento);
			if (par.first == true) {
				par.second += this->getSuperficie().origen();
				return par;
			}
		}
		return std::make_pair(false, Rect());
	}
}

void Contenedor::resized (Vec2 tam) {
	dirty_ = true;
	for (auto& emt : listarElementos()) {
		emt->getFuente()->padreResizeado(tam);
	}
}

void Contenedor::setPermitirEliminaciones (bool permitido){
	permitirEliminaciones = permitido;
}

void Contenedor::quitarElemento(vista::Elemento* elemento){
	for (auto& par : elementos) {
		par.second.remove(elemento);
	}
	dirty_ = true;
}

void Contenedor::vaciar() {
	for (auto& elemento : listarElementos()) {
		delete elemento;
	}
	elementos.clear();
	dirty_ = true;
}

LayoutInfo Contenedor::getLayoutInfo(){
	return LayoutInfo(Vec2(), Vec2(), true, true);
}

vista::Elemento* Contenedor::buscar_base (Vec2 posicionPadre) {
	Vec2 pos = posicionPadre - fuente->getSuperficie().origen();
	for (auto& par : elementos) {
		for (auto& elemento : par.second) {
			if (elemento->contiene(pos)) {
				return elemento;
			}
		}
	}
	return nullptr;
}

std::list<vista::Elemento*> Contenedor::listarElementos () {
	std::list<vista::Elemento*> retval;
	for (auto& par : elementos) {
		retval.insert(retval.end(), par.second.begin(), par.second.end());
	}
	return retval;
}
