#ifndef ORIGENDESTINODIBUJO_H_
#define ORIGENDESTINODIBUJO_H_

struct SDL_Texture;
struct SDL_Renderer;
class FuentePosicion;
class Vec2;

class Dibujable
{
public:
	virtual ~Dibujable () {}

	virtual bool valido () = 0;
	virtual SDL_Texture* getTexture () = 0;
	virtual SDL_Renderer* getRenderer () = 0;
	virtual Vec2 tamDibujo () const = 0;
};

class DestinoDibujo : public Dibujable
{
public:
	virtual ~DestinoDibujo () {}
};

class OrigenDibujo : public Dibujable
{
public:
	virtual ~OrigenDibujo () {}

	void dibujar (DestinoDibujo& destino);
	void dibujar (DestinoDibujo& destino, FuentePosicion& fuente);
};

#endif /* ORIGENDESTINODIBUJO_H_ */
