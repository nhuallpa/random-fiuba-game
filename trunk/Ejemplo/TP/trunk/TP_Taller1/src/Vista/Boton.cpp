/*
 * Boton.cpp
 *
 *  Created on: 14/09/2013
 *  Last Amended: 14/09/2013
 *      Author: natuchis
 */

#include "Boton.h"

#include "Log/Suceso.h"
#include "Utils/make_unique.h"
#include "Utils/Rect.h"
#include "Utils/Vec2.h"
#include "Vista/ClickInfo.h"
#include "Vista/LayoutInfo.h"
#include "Vista/Interfases/Elemento.h"
#include "Vista/FuentesPosicion/FuentePosicion.h"

Boton::Boton(const FuentePosicion& fuente, Imagen imagen, std::function<void()> reaccion,
		std::string imagenUp, std::string imagenDown, bool cambiante)
	: vista::Elemento(fuente)
	, imagen(make_unique<Imagen>(std::move(imagen)))
	, reaccion(reaccion)
	, up(true)
	, imagenUp(imagenUp)
	, imagenDown(imagenDown)
	, cambiante(cambiante)
{
}

Boton::Boton(const FuentePosicion& fuente, Textura textura, std::function<void()> reaccion)
	: vista::Elemento(fuente)
	, imagen(make_unique<Textura>(std::move(textura)))
	, reaccion(reaccion)
	, up(true)
	, imagenUp("")
	, imagenDown("")
	, cambiante(false)
{
}

Boton::~Boton() {
}

void Boton::dibujarse(DestinoDibujo* window) {
	//Acordarse que las posiciones de los elementos que guardamos
	//siempre son relativas a la posicion del contenedor.
	imagen->dibujar(*window, *fuente);
}

vista::ClickInfo Boton::recibirClick (Vec2) {
	reaccion();
	up = false;
	vista::ClickInfo info = vista::ClickInfo();
	info.esBotonCambiante = cambiante;
	info.clickeado = this;
	return info;
}


void Boton::cambiarImagen(std::string path) {
	imagen = make_unique<Imagen>(path, imagen.get());
}

void Boton::cambiarImagen() {
	if (!cambiante) return;
	if (!up) {
		cambiarImagen(imagenDown);
		up = true;
	} else {
		cambiarImagen(imagenUp);
	}
}

bool Boton::dirty() {
	return true;
}

LayoutInfo Boton::getLayoutInfo(){
	return LayoutInfo(imagen->tamDibujo());
}
