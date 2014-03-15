/*
 * Cursor.cpp
 *
 *  Created on: 11/10/2013
 *  Last Amended: 11/10/2013
 *      Author: natuchis
 */

#include "Cursor.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

Cursor::Cursor()
	: cursor(nullptr)
{
}

Cursor::Cursor(std::string path, int x, int y)
	: cursor(NULL)
{
	SDL_Surface* superficieMulPun = IMG_Load (path.c_str());
	cursor = SDL_CreateColorCursor(superficieMulPun,x,y);
	SDL_FreeSurface(superficieMulPun);
}

Cursor::Cursor (Cursor&& base)
	: cursor(base.cursor)
{
	base.cursor = nullptr;
}

Cursor& Cursor::operator= (Cursor&& base) {
	if (cursor != nullptr) {
		SDL_FreeCursor(cursor);
		cursor = nullptr;
	}
	std::swap(cursor, base.cursor);
	return *this;
}

Cursor::~Cursor() {
	if (cursor != nullptr) {
		SDL_FreeCursor(cursor);
	}
}

void Cursor::mostrar() {
	SDL_ShowCursor(SDL_ENABLE);
}

void Cursor::ocultar() {
	SDL_ShowCursor(SDL_DISABLE);
}

void Cursor::activar() {
	SDL_SetCursor(cursor);
	mostrar();
}
