#ifndef RECT_H_
#define RECT_H_

#include "Vec2.h"

struct SDL_Rect;

/* Clase para representar genericamente rectangulos */
class Rect
{
public:
	Rect ();
	Rect (float x, float y, float w, float h);
	Rect (const Vec2& up_left, const Vec2& tam);
	static Rect deCentro (const Vec2& centro, const Vec2& tam);

	Rect (const Rect&) = default;
	Rect (Rect&&) = default;
	Rect& operator= (const Rect&) = default;
	Rect& operator= (Rect&&) = default;
	~Rect () = default;

	Vec2 origen () const;
	void setOrigen (const Vec2& nOrigen);
	Vec2 centro () const;
	void setCentro (const Vec2& nCentro);
	Vec2 tam () const;
	void setTam (const Vec2& nTam);

	bool contiene (Vec2 punto) const;
	bool contiene(Vec2 punto, float miAngulo);

	float radio () const;
	bool colisiona (Rect otro) const;
	bool colisiona (float miAngulo, Rect otro, float anguloOtro) const;

	Rect operator+ (Vec2 delta) const;
	Rect& operator+= (Vec2 delta);

	Rect cambioCoordenadas (const Rect& sistOrigen, const Rect& sistDestino) const;

	// conversiones para SDL
	SDL_Rect aSDL_Rect() const;
	Rect (SDL_Rect base);
	
private:
	Vec2 up_left;
	Vec2 down_right;
};

#endif /* RECT_H_ */
