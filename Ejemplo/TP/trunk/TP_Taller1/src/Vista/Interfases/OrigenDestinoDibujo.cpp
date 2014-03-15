#include "OrigenDestinoDibujo.h"

#include "Log/Suceso.h"
#include "Utils/Rect.h"
#include "Utils/Vec2.h"
#include "Vista/FuentesPosicion/FuentePosicion.h"

#include <SDL2/SDL.h>

void OrigenDibujo::dibujar (DestinoDibujo& destino)
{
	if (!this->valido()) {
		Log::Suceso(Log::DEBUG, "Intento dibujar origen invalido");
		return;
	} else if (!destino.valido()) {
		Log::Suceso(Log::DEBUG, "Intento dibujar destino invalido");
		return;
	}

	SDL_Renderer *ren = destino.getRenderer();

	SDL_SetRenderTarget(ren, destino.getTexture());
	SDL_RenderCopy(ren, getTexture(), NULL, NULL);
}

void OrigenDibujo::dibujar (DestinoDibujo& destino, FuentePosicion& fuente)
{
	if (!this->valido()) {
		Log::Suceso(Log::DEBUG, "Intento dibujar origen invalido");
		return;
	} else if (!destino.valido()) {
		Log::Suceso(Log::DEBUG, "Intento dibujar destino invalido");
		return;
	}

	Rect sistOrigen(Vec2(0, 0), fuente.getTamPadre());
	Rect sistDestino(Vec2(0, 0), destino.tamDibujo());
	Rect regionImagen = fuente.getSuperficie().cambioCoordenadas(sistOrigen, sistDestino);

	SDL_Rect sdlRegion(regionImagen.aSDL_Rect());

	SDL_Renderer *ren = destino.getRenderer();

	SDL_SetRenderTarget(ren, destino.getTexture());
	SDL_RenderCopyEx(ren, getTexture(), NULL, &sdlRegion, fuente.getAngulo(), NULL, SDL_FLIP_NONE);
}
