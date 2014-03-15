#include "Imagen.h"

#include "Interfases/OrigenDestinoDibujo.h"
#include "Log/Suceso.h"
#include "Utils/Vec2.h"
#include "Utils/Rect.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdexcept>
#include <vector>
#include <map>

using namespace std;

struct ImagenReal
{
	ImagenReal ();
	ImagenReal (SDL_Renderer *destino);
	ImagenReal (const std::string &path, SDL_Renderer *destino);

	ImagenReal (const ImagenReal&) = delete;
	ImagenReal (ImagenReal&&) = default;
	ImagenReal& operator= (const ImagenReal&) = delete;
	ImagenReal& operator= (ImagenReal&&) = default;
	virtual ~ImagenReal ();

	Vec2 tam;
	SDL_Texture *tex;
	SDL_Renderer *rend;
	vector<bool> bitmapEsTransparente;

	static map<pair<SDL_Renderer*, string>, weak_ptr<ImagenReal>> cache;
	static map<SDL_Renderer*, shared_ptr<ImagenReal>> imagenDefault;
};

map<pair<SDL_Renderer*, string>, weak_ptr<ImagenReal>> ImagenReal::cache;
map<SDL_Renderer*, shared_ptr<ImagenReal>> ImagenReal::imagenDefault;

ImagenReal::ImagenReal ()
	: tam()
	, tex(NULL)
	, rend(NULL)
	, bitmapEsTransparente()
{
}

ImagenReal::ImagenReal (SDL_Renderer* ren)
	: tam(100, 100)
	, tex(NULL)
	, rend(ren)
	, bitmapEsTransparente(tam.x * tam.y, false)
{
	tex = SDL_CreateTexture(ren, SDL_PIXELFORMAT_RGBA8888,
	                        SDL_TEXTUREACCESS_TARGET, 100, 100);
	if (tex == NULL) {
		std::string mensaje("No se pudo crear imagen por defecto: ");
		mensaje = mensaje + SDL_GetError();
		throw Log::Suceso(Log::ERROR, mensaje);
	}

	SDL_SetRenderTarget(ren, tex);
	SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
	SDL_RenderDrawLine(ren, 0, 0, 100, 100);
	SDL_RenderDrawLine(ren, 0, 100, 100, 0);
}

Uint8 obtenerAlpha (SDL_Surface *img, int x, int y)
{
	Uint8 *base = (Uint8 *)img->pixels + img->pitch * y + img->format->BytesPerPixel * x;
	Uint32 pixel;
	switch (img->format->BytesPerPixel) {
	case 1:
		pixel = *base;
		break;

	case 2:
		pixel = *(Uint16 *)base;
		break;

	case 3:
		if (SDL_BYTEORDER == SDL_BIG_ENDIAN) {
			pixel = base[2] | base[1] << 8 | base[0] << 16;
		} else {
			pixel = base[0] | base[1] << 8 | base[2] << 16;
		}
		break;

	case 4:
		pixel = *(Uint32 *)base;
		break;
	}

	Uint8 r, g, b, a;
	SDL_GetRGBA(pixel, img->format, &r, &g, &b, &a);

	return a;
}

ImagenReal::ImagenReal (const std::string &path, SDL_Renderer *ren)
	: tam()
	, tex(NULL)
	, rend(ren)
	, bitmapEsTransparente()
{
	SDL_Surface *loadedImage = IMG_Load(path.c_str());
	if (loadedImage == NULL) {
		std::string mensaje("No se pudo cargar imagen: ");
		mensaje = mensaje + IMG_GetError();
		throw Log::Suceso(Log::ERROR, mensaje);
	}

	tex = SDL_CreateTextureFromSurface(ren, loadedImage);
	tam = Vec2(loadedImage->w, loadedImage->h);
	if (tex == NULL) {
		SDL_FreeSurface(loadedImage);
		std::string mensaje("No se pudo crear imagen: ");
		mensaje = mensaje + SDL_GetError();
		throw Log::Suceso(Log::ERROR, mensaje);
	}

	bitmapEsTransparente.resize(tam.x * tam.y, false);
	SDL_LockSurface(loadedImage);
	for (int j = 0; j < tam.y; ++j) {
		for (int i = 0; i < tam.x; ++i) {
			if (obtenerAlpha(loadedImage, i, j) < 200) {
				bitmapEsTransparente[tam.x * (tam.y - j - 1) + i] = true;
			}
		}
	}
	SDL_FreeSurface(loadedImage);
}

ImagenReal::~ImagenReal ()
{
	SDL_DestroyTexture(tex);
}



Imagen::Imagen ()
	: impl(nullptr)
{
}

Imagen::Imagen (const std::string &path, Dibujable *destino)
	: impl(NULL)
{
	auto ren = destino->getRenderer();
	auto clave = make_pair(ren, path);
	if (ImagenReal::cache[clave].expired()) {
		ImagenReal imagen;
		try {
			impl = make_shared<ImagenReal>(path, ren);
		} catch (Log::Suceso&) {
			if (!ImagenReal::imagenDefault[ren]) {
				ImagenReal::imagenDefault[ren] = make_shared<ImagenReal>(ren);
			}
			impl = ImagenReal::imagenDefault[ren];
		}
		ImagenReal::cache[clave] = weak_ptr<ImagenReal>(impl);
	} else {
		impl = ImagenReal::cache[clave].lock();
	}
}

Imagen::~Imagen ()
{
}

Vec2 Imagen::tamDibujo () const
{
	return impl->tam;
}

bool Imagen::esTransparente (Vec2 pos)
{
	if (!Rect(Vec2(), impl->tam).contiene(pos)) {
		return true;
	}
	return impl->bitmapEsTransparente[impl->tam.x * floor(pos.y) + floor(pos.x)];
}

bool Imagen::valido()
{
	return bool(impl);
}

SDL_Renderer *Imagen::getRenderer ()
{
	return impl->rend;
}

SDL_Texture *Imagen::getTexture ()
{
	return impl->tex;
}

