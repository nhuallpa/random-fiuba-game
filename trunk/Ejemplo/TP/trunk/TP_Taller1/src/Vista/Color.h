#ifndef COLOR_H_
#define COLOR_H_

#include <array>
#include <cstdint>

class SDL_Color;

namespace vista {

class Color
{
public:
	Color ();
	Color (uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);

	Color (const Color&) = default;
	Color (Color&&) = default;
	Color& operator= (const Color&) = default;
	Color& operator= (Color&&) = default;
	~Color() = default;

	Color mezclar (Color otro);
	Color modular (Color otro);

	// conversiones para sdl
	operator SDL_Color ();
	Color (SDL_Color);

	// magia para poder acceder o iterar
	union {
		uint8_t datos[4];
		struct {
			uint8_t r;
			uint8_t g;
			uint8_t b;
			uint8_t a;
		};
	};
};

} /* namespace vista */
#endif /* COLOR_H_ */
