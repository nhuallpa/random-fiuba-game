/*
 * Ventana.cpp
 *
 *  Created on: Sep 5, 2013
 *      Author: lucia
 */

#include "Ventana.h"

#include "Log/Suceso.h"
#include "Utils/Vec2.h"
#include "Vista/Contenedor.h"
#include <SDL2/SDL.h>

Ventana::Ventana(int width, int height, std::string title)
	: superficie()
	, window(NULL)
	, ren(NULL)
	, raiz()
{
	window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED,
	                          SDL_WINDOWPOS_CENTERED, width, height,
	                          SDL_WINDOW_HIDDEN | SDL_WINDOW_RESIZABLE);
	if (window == NULL) {
		std::string mensaje("No se creo ventana: ");
		mensaje = mensaje + SDL_GetError();
		throw Log::Suceso(Log::FATAL, mensaje);
	}

	int x, y, w, h;
	SDL_GetWindowPosition(window, &x, &y);
	SDL_GetWindowSize(window, &w, &h);
	superficie = Rect(x, y, w, h);

	ren = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_TEXTUREACCESS_TARGET);
	if (this->ren == NULL) {
		SDL_DestroyWindow(window);

		std::string mensaje("No se creo renderer: ");
		mensaje = mensaje + SDL_GetError();
		throw Log::Suceso(Log::FATAL, mensaje);
	}

	SDL_RenderClear(this->ren);
	SDL_ShowWindow(this->window);
	Log::Suceso(Log::INFO, "Creada ventana.");
}

Ventana::~Ventana() {
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(window);
}

SDL_Renderer* Ventana::getRenderer (){
	return this->ren;
}

bool Ventana::valido () {
	return window != nullptr;
}

SDL_Texture* Ventana::getTexture (){
	return NULL; //indica que quiero escribir a la ventana en si
}

Vec2 Ventana::tamDibujo() const{
	return superficie.tam();
}

void Ventana::resized (Vec2 tam) {
	superficie = Rect(superficie.origen(), tam);
	raiz->resized(tam);
}

void Ventana::moved (Vec2 pos) {
	superficie = Rect(pos, superficie.tam());
}

void Ventana::setSuperficie (Rect nSuperficie) {
	SDL_SetWindowPosition(window, nSuperficie.origen().x, nSuperficie.origen().y);
	SDL_SetWindowSize(window, nSuperficie.tam().x, nSuperficie.tam().y);
	superficie = nSuperficie;
}

Rect Ventana::getSuperficie () const {
	return superficie;
}

void Ventana::update () {
	SDL_SetRenderTarget(ren, NULL);
	SDL_RenderClear(ren);
	if (raiz) {
		raiz->dibujarse(this);
	}
	SDL_RenderPresent(ren);
}

void Ventana::setRaiz (std::unique_ptr<Contenedor> nRaiz) {
	raiz = std::move(nRaiz);
}

std::unique_ptr<Contenedor> Ventana::extraerRaiz () {
	return std::move(raiz);
}

Contenedor* Ventana::getRaiz () const {
	return raiz.get();
}
