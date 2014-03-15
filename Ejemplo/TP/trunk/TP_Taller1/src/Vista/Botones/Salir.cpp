/*
 * Salir.cpp
 *
 *  Created on: 14/09/2013
 *  Last Amended: 15/09/2013
 *      Author: natuchis
 */

#include "Salir.h"

#include <SDL2/SDL_events.h>

Salir::Salir(const FuentePosicion& fuente, Dibujable *destino)
	: Boton(fuente,
		Imagen("imagenes/botones/Salir.png", destino),
		[] {
			SDL_Event evento;
			evento.type = SDL_QUIT;
			SDL_PushEvent(&evento);
		}, "imagenes/botones/Salir.png",
		"imagenes/botones/SalirDown.png",
		true)
{
}

Salir::~Salir() {
}
