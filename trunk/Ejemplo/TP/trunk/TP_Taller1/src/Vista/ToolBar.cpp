/*
 * ToolBar.cpp
 *
 *  Created on: 15/09/2013
 *      Author: stephanie
 */

#include "ToolBar.h"

#include "Modelo/Juego.h"
#include "Utils/iteracion.h"
#include "Utils/Rect.h"
#include "Vista/Canvas.h"
#include "Vista/ClickInfo.h"
#include "Vista/FalsaFigura.h"
#include "Vista/Imagen.h"
#include "Vista/LayoutInfo.h"
#include "Vista/Textura.h"
#include "Vista/FuentesPosicion/FuenteToolBar.h"

#include <algorithm>
#include <SDL2/SDL_rect.h>

const int ToolBar::espacioEntreFiguras = 20;
const int ToolBar::desplazamientoInicial = 10;
const float ToolBar::desplazamientoFraccional = 0.05f;
const float ToolBar::tamFiguraEnUL = 1.0;

ToolBar::ToolBar(const FuentePosicion& fuente, Dibujable* destino, Canvas *canvas, Modelo::Juego *juego)
       : Contenedor(fuente, destino)
       , posicionEnToolbar(desplazamientoInicial)
       , canvas(canvas)
       , juego(juego)
{
	if (juego->miJugador == Modelo::TipoJugador::Escenario) {
		for (auto& tipo : Modelo::listaTipoElemento) {
			FuenteToolBar fuente(this);
			addElemento(new vista::FalsaFigura(fuente, tipo, destino, 9999));
		}
	} else {
		for (auto& par : juego->jugadores[juego->miJugador].entidadesDisponibles) {
			FuenteToolBar fuente(this);
			addElemento(new vista::FalsaFigura(fuente, par.first, destino, par.second));
		}
	}
}

ToolBar::~ToolBar() {
}

void ToolBar::subirToolBar(){

	if (listarElementos().size() != 0) {
		int y = listarElementos().front()->getSuperficie().origen().y;
		y = y + listarElementos().front()->getSuperficie().aSDL_Rect().h;

		if (y > fuente->getSuperficie().aSDL_Rect().h){
			posicionEnToolbar -= fuente->getSuperficie().tam().y * desplazamientoFraccional;
		}
		dirty_ = true;
	}
}

void ToolBar::bajarToolBar(){
	if (listarElementos().size() != 0) {
		int y = listarElementos().back()->getSuperficie().aSDL_Rect().y;
		if (y <= fuente->getSuperficie().aSDL_Rect().y){
			posicionEnToolbar += fuente->getSuperficie().tam().y * desplazamientoFraccional;
		}
		dirty_ = true;
	}
}

void ToolBar::desplazarHaciaAbajo(Vec2){
	bajarToolBar();
}

void ToolBar::desplazarHaciaArriba(Vec2){
	subirToolBar();
}

vista::ClickInfo ToolBar::recibirClick(Vec2 posicionMouse) {
	vista::ClickInfo retval = Contenedor::recibirClick(posicionMouse);
	retval.puedeRotar = false;
	retval.puedeResizear = false;
	return retval;
}

void ToolBar::regenerar() {

	int posicionOrigenEnToolbar = this->posicionEnToolbar;
	auto elementos = listarElementos();
	for (auto& elemento : invertir_iteracion(elementos)) {
		actualizarSuperficiesFiguras(elemento);
		actualizarPosicionEnToolbar(elemento->getSuperficie());
		if (juego->miJugador != Modelo::TipoJugador::Escenario) {
			actualizarCantidad(elemento);
		}
	}
	posicionEnToolbar = posicionOrigenEnToolbar;

	Contenedor::regenerar();
	dirty_ = false;
}

LayoutInfo ToolBar::getLayoutInfo(){
	Vec2 tamFigura = canvas->tamUnidadLogica() * tamFiguraEnUL;

	Vec2 tamMinimo = tamFigura;
	Vec2 tamPreferido = tamFigura * 2 + Vec2(1, 1);
	return LayoutInfo(tamPreferido, tamMinimo, false, true);
}

bool ToolBar::dirty() {
	//TODO: cambiar cuando responda al resize de ventana
	return Contenedor::dirty();
	//return dirty_;
}

int ToolBar::getPosicionEnToolbar(){
	return posicionEnToolbar;
}

void ToolBar::actualizarPosicionEnToolbar(Rect fig){
	posicionEnToolbar += fig.aSDL_Rect().h + espacioEntreFiguras;
}

void ToolBar::actualizarSuperficiesFiguras(vista::Elemento* figura){
	Rect superficie;
	float anchoToolbar = this->getSuperficie().tam().x;

	Vec2 centroSuperior(anchoToolbar/2, this->getPosicionEnToolbar());
	Vec2 nTam = canvas->tamUnidadLogica() * tamFiguraEnUL;

	superficie.setTam(nTam);
	superficie.setCentro(centroSuperior + Vec2(0.0, nTam.y/2));

	figura->setSuperfice(superficie);
}

void ToolBar::actualizarCantidad (vista::Elemento* elemento) {
	auto figura = dynamic_cast<vista::FalsaFigura*>(elemento);
	if (figura == nullptr) return;

	auto& jugador = juego->jugadores[juego->miJugador];
	auto tipo = figura->getTipo();
	if (jugador.entidadesDisponibles.count(tipo) != 0) {
		size_t enCanvas = canvas->getCuenta(juego->miJugador, tipo);
		size_t enArrastre = 0;
		if (jugador.estadoMouse == controlador::Mouse::Estado::arrastrando && jugador.elementoMouse == tipo) {
			enArrastre = 1;
		}
		figura->setCantidad(jugador.entidadesDisponibles.at(figura->getTipo()) - enCanvas - enArrastre);
	}
}
