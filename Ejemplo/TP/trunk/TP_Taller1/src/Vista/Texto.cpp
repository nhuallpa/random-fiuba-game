/*
 * Texto.cpp
 *
 *  Created on: 02/10/2013
 *  Last Amended: 02/10/2013
 *      Author: natuchis
 */

#include "Texto.h"

#include "Log/Suceso.h"
#include "Utils/Rect.h"
#include "Utils/Vec2.h"
#include "Vista/Color.h"
#include "Vista/Textura.h"
#include "Vista/FuentesPosicion/FuenteFuncion.h"
#include <SDL2/SDL_ttf.h>
#include <utility>

struct Texto::Impl
{
	Impl (Dibujable* destino, std::string textoInicial);

	Impl (const Impl&) = delete;
	Impl (Impl&&) = delete;
	Impl& operator= (const Impl&) = delete;
	Impl& operator= (Impl&&) = delete;
	~Impl();

	Textura apariencia;
	std::shared_ptr<TTF_Font> fuenteTexto;
	vista::Color colorTexto;
	vista::Color colorFondo;
	std::string texto;
	bool necesitaRegenerar;

	static std::weak_ptr<TTF_Font> cacheFuenteTexto;
};

std::weak_ptr<TTF_Font> Texto::Impl::cacheFuenteTexto;

Texto::Impl::Impl (Dibujable* destino, std::string textoInicial)
	: apariencia()
	, fuenteTexto()
	, colorTexto(0, 0, 0, 255)
	, colorFondo(255, 255, 240, 255)
	, texto(textoInicial)
	, necesitaRegenerar(false)
{
	if (cacheFuenteTexto.expired()) {
		TTF_Font *ptr = TTF_OpenFont("fonts/Arial_Bold.ttf", 14);
		if (ptr != nullptr) {
			std::function<void(TTF_Font*)> deleter = [] (TTF_Font* ptr) {
				if (TTF_WasInit()) TTF_CloseFont(ptr);
			};
			fuenteTexto = std::shared_ptr<TTF_Font>(ptr, deleter);
			Log::Suceso(Log::INFO, "Fuente arial bold iniciado correctamente.");
		} else {
			std::string mensaje("Fallo al iniciar la fuente: ");
			mensaje += TTF_GetError();
			throw Log::Suceso(Log::FATAL, mensaje);
		}
		cacheFuenteTexto = fuenteTexto;
	} else {
		fuenteTexto = cacheFuenteTexto.lock();
	}
}

Texto::Impl::~Impl () {
}



Texto::Texto()
	: impl(nullptr)
{
}

Texto::Texto(Dibujable* destino, std::string textoInicial)
	: impl(new Impl(destino, std::move(textoInicial)))
{
	setApariencia(*destino);
}

Texto::~Texto() {
}

bool Texto::valido() {
	return impl->apariencia.valido();
}

SDL_Renderer* Texto::getRenderer() {
	return impl->apariencia.getRenderer();
}

SDL_Texture *Texto::getTexture() {
	if (impl->necesitaRegenerar) {
		regenerar();
	}
	return impl->apariencia.getTexture();
}

void Texto::dibujarse(DestinoDibujo* destino, Rect superficie, Vec2 padre) {
	if (impl->necesitaRegenerar) {
		regenerar();
	}
	FuenteFuncion fuente(
			[superficie] { return superficie; },
			[] { return 0; },
			[] { return true; },
			[padre] { return padre; });
	impl->apariencia.dibujar(*destino, fuente);
}

Vec2 Texto::tamDibujo () const {
	if (impl->necesitaRegenerar) {
		regenerar();
	}
	return impl->apariencia.tamDibujo();
}

std::string Texto::getTexto() {
	return impl->texto;
}

void Texto::setTexto(std::string unTexto) {
	impl->texto = unTexto;
	impl->necesitaRegenerar = true;
}

vista::Color& Texto::colorFondo()
{
	return impl->colorFondo;
}

vista::Color& Texto::colorTexto()
{
	return impl->colorTexto;
}

void Texto::regenerar() const {
	setApariencia((DestinoDibujo&)impl->apariencia);
}

void Texto::setApariencia (Dibujable& destino) const {
	std::string aUsar(impl->texto);
	if (aUsar == "") {
		aUsar = " ";
	}
	SDL_Surface *render = TTF_RenderText_Shaded(impl->fuenteTexto.get(), aUsar.c_str(),
	                                            impl->colorTexto, impl->colorFondo);
	if (render == nullptr) {
		std::string mensaje("No se pudo crear texto: ");
		throw Log::Suceso(Log::FATAL, mensaje + TTF_GetError());
	}

	// llamado automaticamente al salir de la funcion, preserva la posible excepcion
	auto deleter = [] (SDL_Surface *val) { SDL_FreeSurface(val); };
	std::unique_ptr<SDL_Surface, decltype(deleter)> puntero(render, deleter);

	impl->apariencia = Textura(destino, render);
}
