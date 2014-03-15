#ifndef TEXTURA_H_
#define TEXTURA_H_

#include "Interfases/OrigenDestinoDibujo.h"

class SDL_Surface;
class Vec2;

namespace vista {
	class Color;
}

class Textura : public DestinoDibujo, public OrigenDibujo
{
public:
	Textura ();
	Textura (Dibujable& superior, SDL_Surface* surface);
	Textura (Dibujable& superior, const Vec2& tam);

	Textura (const Textura&) = delete;
	Textura (Textura&&);
	Textura& operator= (const Textura&) = delete;
	Textura& operator= (Textura&&);
	virtual ~Textura ();

	void limpiar();
	void limpiar(vista::Color);
	void mezclar(vista::Color);

	virtual SDL_Renderer* getRenderer ();
	virtual bool valido ();
	virtual SDL_Texture* getTexture ();
	virtual Vec2 tamDibujo() const;

private:
	SDL_Renderer* renderer;
	SDL_Texture* texture;
};

#endif /* TEXTURA_H_ */
