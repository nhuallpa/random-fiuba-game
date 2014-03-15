/*
 * Textbox.cpp
 *
 *  Created on: 24/09/2013
 *      Author: rick
 */

#include "Textbox.h"

#include "Vista/Color.h"
#include "Vista/ClickInfo.h"
#include "Vista/LayoutInfo.h"
#include "Vista/FuentesPosicion/FuenteLayout.h"

Textbox::Textbox(const FuentePosicion& fuente, Dibujable* destino, std::string textoInicial)
	: vista::Elemento(fuente)
	, apariencia(*destino,fuente.getSuperficie().tam())
	, dirty_(true)
	, texto(destino, textoInicial)
	, respuestaEnter([] (std::string) {})
{
}

Textbox::~Textbox() {
}

LayoutInfo Textbox::getLayoutInfo() {
	return LayoutInfo(Vec2(300, 26), Vec2(150, 25), true, false);
}

void Textbox::regenerar() {
	if (apariencia.tamDibujo() != fuente->getSuperficie().tam()) {
		apariencia = Textura((DestinoDibujo&)apariencia, fuente->getSuperficie().tam());
	}

	Vec2 tamanio = fuente->getSuperficie().tam();
	Vec2 tamanioTexto = texto.tamDibujo() / texto.tamDibujo().y * tamanio.y;
	float delta = std::min(0.0f, tamanio.x - tamanioTexto.x);

	apariencia.limpiar(texto.colorFondo());
	texto.dibujarse(&apariencia, Rect(Vec2(delta, 0), tamanioTexto), tamanio);
	dirty_ = false;
}

void Textbox::dibujarse(DestinoDibujo* destino) {
	if (dirty()) {
		regenerar();
	}
	apariencia.dibujar(*destino, *fuente);
}

bool Textbox::dirty() {
	return dirty_;
}

void Textbox::grabarCaracter(char caracter) {
	std::string nuevoTexto = texto.getTexto();
	if (caracter == '\n') {
		respuestaEnter(nuevoTexto);
	} else {
		if (caracter == '\b') {
			nuevoTexto = nuevoTexto.substr(0, nuevoTexto.size() - 1);
		} else {
			nuevoTexto.push_back(caracter);
		}
		texto.setTexto(nuevoTexto);
		dirty_ = true;
	}
}

vista::ClickInfo Textbox::recibirClick(Vec2 pos) {
	vista::ClickInfo retval(this, pos);
	retval.tomaFocoTeclado = true;
	return retval;
}

std::string Textbox::getTexto() {
	return texto.getTexto();
}

void Textbox::setRespuestaEnter (std::function<void(std::string)> fn) {
	respuestaEnter = fn;
	dirty_ = true;
}

vista::Color& Textbox::colorTexto() {
	dirty_ = true;
	return texto.colorTexto();
}

vista::Color& Textbox::colorFondo() {
	dirty_ = true;
	return texto.colorFondo();
}
