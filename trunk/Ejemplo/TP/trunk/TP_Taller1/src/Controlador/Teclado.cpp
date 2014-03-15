/*
 * Teclado.cpp
 *
 *  Created on: Sep 13, 2013
 *      Author: lucia
 */

#include "Teclado.h"

#include "Vista/Interfases/Elemento.h"

#include <cstddef>

namespace controlador {


Teclado::Teclado()
	: presionadas()
	, elemento(nullptr)
{
}

void Teclado::presionar(SDL_Keycode tecla) {
	presionadas.insert(tecla);
}


void Teclado::soltar(SDL_Keycode tecla) {
	if (elemento != NULL) {
		switch (tecla) {
		case SDLK_BACKSPACE:
			elemento->grabarCaracter('\b');
			break;
		case SDLK_RETURN:
			elemento->grabarCaracter('\n');
			break;
		}
	}
	presionadas.erase(tecla);
}

void Teclado::input (const char* texto) {
	if (elemento != nullptr && texto != nullptr) {
		for (const char* ptr = texto; *ptr != '\0'; ++ptr) {
			elemento->grabarCaracter(*ptr);
		}
	}
}

void Teclado::enfocar (vista::Elemento* emt) {
	//elemento = emt;
}

bool Teclado::presionada(SDL_Keycode tecla) {
	return presionadas.count(tecla) != 0;
}

bool Teclado::shift() {
	return presionada(SDLK_LSHIFT) || presionada(SDLK_RSHIFT);
}

bool Teclado::ctrl() {
	return presionada(SDLK_LCTRL) || presionada(SDLK_RCTRL);
}

bool Teclado::r(){
	return presionada(SDLK_r);
}

bool Teclado::esc(){
	return presionada(SDLK_ESCAPE);
}

bool Teclado::accion(){
	return presionada(SDLK_SPACE);
}

bool Teclado::siguiente() {
	return presionada(SDLK_RIGHT);
}
bool Teclado::anterior() {
	return presionada(SDLK_LEFT);
}
bool Teclado::arriba() {
	return presionada(SDLK_UP);
}
bool Teclado::abajo() {
	return presionada(SDLK_DOWN);
}

} /* namespace controlador */
