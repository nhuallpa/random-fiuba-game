#include "Color.h"

#include <SDL2/SDL_video.h>

namespace vista {

Color::Color ()
	: datos{0, 0, 0, 0}
{
}

Color::Color (uint8_t r, uint8_t g, uint8_t b, uint8_t a)
	: datos{r, g, b, a}
{
}

Color Color::mezclar (Color otro)
{
	Color nColor;
	for (unsigned i = 0; i < 4; ++i) {
		nColor.datos[i] = datos[i] * (1 - datos[3]) + otro.datos[i] * otro.datos[3];
	}
	return nColor;
}

Color Color::modular (Color otro)
{
	Color nColor;
	for (unsigned i = 0; i < 4; ++i) {
		nColor.datos[i] = datos[i] * otro.datos[i];
	}
	return nColor;
}

Color::operator SDL_Color ()
{
	SDL_Color retval;
	retval.r = datos[0];
	retval.g = datos[1];
	retval.b = datos[2];
	retval.a = datos[3];
	return retval;
}

Color::Color (SDL_Color base)
	: datos{base.r, base.g, base.b, base.a}
{
}

} /* namespace vista */
