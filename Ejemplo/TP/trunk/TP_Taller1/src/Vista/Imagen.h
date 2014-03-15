#ifndef IMAGEN_H_
#define IMAGEN_H_

#include "Interfases/OrigenDestinoDibujo.h"
#include <string>
#include <memory>

class DestinoDibujo;
class Vec2;
struct SDL_Texture;
struct SDL_Renderer;
struct ImagenReal;

class Imagen : public OrigenDibujo
{
public:
	Imagen ();
	Imagen (const std::string &path, Dibujable *rend);

	Imagen (const Imagen&) = default;
	Imagen (Imagen&&) = default;
	Imagen& operator= (const Imagen&) = default;
	Imagen& operator= (Imagen&&) = default;
	virtual ~Imagen ();

	bool esTransparente(Vec2 pos);

	virtual bool valido ();
	virtual SDL_Renderer *getRenderer ();
	virtual SDL_Texture *getTexture ();
	virtual Vec2 tamDibujo () const;

private:
	std::shared_ptr<ImagenReal> impl;
};

#endif /* IMAGEN_H_ */
