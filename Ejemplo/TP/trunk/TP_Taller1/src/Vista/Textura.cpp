#include "Textura.h"

#include "Log/Suceso.h"
#include "Utils/Rect.h"
#include "Utils/Vec2.h"
#include "Vista/Color.h"
#include <SDL2/SDL.h>
#include <cmath>

Textura::Textura ()
	: renderer(nullptr)
	, texture(nullptr)
{
}

Textura::Textura (Dibujable& superior, SDL_Surface* surface)
	: renderer(superior.getRenderer())
	, texture(NULL)
{
	texture = SDL_CreateTextureFromSurface(superior.getRenderer(), surface);
	if (texture == NULL) {
		std::string mensaje("Textura nula: ");
		mensaje = mensaje + SDL_GetError();
		throw Log::Suceso(Log::ERROR, mensaje);
	}
}

Textura::Textura (Dibujable& superior, const Vec2& tam)
	: renderer(superior.getRenderer())
	, texture(NULL)
{
	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
	                            SDL_TEXTUREACCESS_TARGET, std::ceil(tam.x), std::ceil(tam.y));
	if (texture == NULL) {
		std::string mensaje("Textura nula: ");
		mensaje = mensaje + SDL_GetError();
		throw Log::Suceso(Log::ERROR, mensaje);
	}
	limpiar();
}

Textura::Textura (Textura&& base)
	: renderer(base.renderer)
	, texture(base.texture)
{
	base.texture = nullptr;
}

Textura& Textura::operator= (Textura&& base)
{
	using std::swap;
	swap(this->renderer, base.renderer);
	swap(this->texture, base.texture);
	return *this;
}

Textura::~Textura ()
{
	if (texture != nullptr) {
		SDL_DestroyTexture(texture);
	}
}

void Textura::limpiar ()
{
	SDL_SetRenderTarget(renderer, texture);
	SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);
}

void Textura::limpiar (vista::Color c)
{
	SDL_SetRenderTarget(renderer, texture);
	SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
	SDL_RenderClear(renderer);
}

void Textura::mezclar (vista::Color c)
{
	SDL_SetRenderTarget(renderer, texture);
	SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

	SDL_Rect supTotal = Rect(Vec2(), tamDibujo()).aSDL_Rect();
	SDL_RenderFillRect(renderer, &supTotal);

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
}

SDL_Renderer* Textura::getRenderer()
{
	return renderer;
}

bool Textura::valido()
{
	return texture != nullptr;
}

SDL_Texture* Textura::getTexture()
{
	return texture;
}

Vec2 Textura::tamDibujo() const
{
	int x, y;
	SDL_QueryTexture(texture, NULL, NULL, &x, &y);
	return Vec2(x, y);
}

