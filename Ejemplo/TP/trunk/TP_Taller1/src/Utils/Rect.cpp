#include "Rect.h"

#include "Vec2.h"
#include <algorithm>
#include <array>
#include <functional>
#include <SDL2/SDL_rect.h>

Rect::Rect ()
	: up_left(0, 0)
	, down_right(0, 0)
{
}

Rect::Rect (float x, float y, float w, float h)
	: up_left(x, y)
	, down_right(x+w, y+h)
{
}

Rect::Rect (const Vec2& up_left, const Vec2& tam)
	: up_left(up_left)
	, down_right(up_left + tam)
{
}

Rect Rect::deCentro (const Vec2& centro, const Vec2& tam)
{
	return Rect(centro - tam/2, tam);
}

Vec2 Rect::origen () const
{
	return up_left;
}

Vec2 Rect::centro () const
{
	return (up_left + down_right) / 2;
}

Vec2 Rect::tam () const
{
	return down_right - up_left;
}

bool Rect::contiene (Vec2 punto) const
{
	return up_left.x <= punto.x && punto.x <= down_right.x && up_left.y <= punto.y && punto.y <= down_right.y;
}

bool Rect::colisiona (Rect otro) const
{
	// chequeo que algun maximo de uno sea menor a un minimo asociado del otro
	if (otro.down_right.x < up_left.x ||
	    down_right.x < otro.up_left.x ||
	    up_left.y > otro.down_right.y ||
	    otro.up_left.y > down_right.y) {
		return false;
	}
	return true;
}

float Rect::radio () const
{
	return (tam()/2).abs();
}

bool tiene_separacion (Rect lhs, float al, Rect rhs, float ar)
{
	/* Implementacion horrible de http://en.wikipedia.org/wiki/Separating_axis_theorem */
	// Transformo rhs tal que lhs este centrado y paralelo a los ejes.
	Vec2 centro = (rhs.centro() - lhs.centro()).rotar(al);
	float angulo = al - ar;
	Vec2 diagonal = rhs.tam() / 2;

	std::array<Vec2, 4> esquinas = {{
		centro + (diagonal * Vec2( 1, 1)).rotar(angulo),
		centro + (diagonal * Vec2(-1, 1)).rotar(angulo),
		centro + (diagonal * Vec2(-1,-1)).rotar(angulo),
		centro + (diagonal * Vec2( 1,-1)).rotar(angulo),
	}};
	Vec2 separaciones = lhs.tam() / 2;

	// veo si alguno de los lados sirve como separacion
	std::array<std::function<bool(Vec2)>, 4> predicados = {{
		[separaciones] (Vec2 punto) -> bool { return separaciones.x < punto.x; },
		[separaciones] (Vec2 punto) -> bool { return punto.x < -separaciones.x; },
		[separaciones] (Vec2 punto) -> bool { return punto.y < -separaciones.y; },
		[separaciones] (Vec2 punto) -> bool { return separaciones.y < punto.y; },
	}};
	for (auto& pred : predicados) {
		if (std::all_of(begin(esquinas), end(esquinas), pred)) {
			return true;
		}
	}
	return false;
}

bool Rect::colisiona (float miAngulo, Rect otro, float anguloOtro) const
{
	return !tiene_separacion(*this, miAngulo, otro, anguloOtro) &&
	       !tiene_separacion(otro, anguloOtro, *this, miAngulo);
}

Rect Rect::operator+ (Vec2 delta) const
{
	Rect retval(*this);
	retval.up_left += delta;
	retval.down_right += delta;
	return retval;
}

Rect& Rect::operator+= (Vec2 delta)
{
	*this = *this + delta;
	return *this;
}

Rect Rect::cambioCoordenadas (const Rect& sistOrigen, const Rect& sistDestino) const
{
	Vec2 ul = up_left.cambioCoordenadas(sistOrigen, sistDestino);
	Vec2 dr = down_right.cambioCoordenadas(sistOrigen, sistDestino);
	return Rect(ul, dr - ul);
}

SDL_Rect Rect::aSDL_Rect () const
{
	SDL_Rect retval;
	retval.x = up_left.x;
	retval.y = up_left.y;
	retval.w = tam().x;
	retval.h = tam().y;
	return retval;
}

Rect::Rect (SDL_Rect base)
	: up_left(base.x, base.y)
	, down_right(up_left + Vec2(base.w, base.h))
{
}

void Rect::setOrigen (const Vec2& nOrigen)
{
	Vec2 tamActual(tam());
	up_left = nOrigen;
	down_right = nOrigen + tamActual;
}

void Rect::setCentro (const Vec2& nCentro)
{
	Vec2 tamActual(tam());
	up_left = nCentro - tamActual / 2;
	down_right = up_left + tamActual;
}

void Rect::setTam (const Vec2& nTam)
{
	Vec2 centroActual(centro());
	up_left = centroActual - nTam / 2;
	down_right = up_left + nTam;
}

bool Rect::contiene(Vec2 punto, float miAngulo) {
	Vec2 puntoRotado = centro() + (punto - centro()).rotar(miAngulo);
	return contiene(puntoRotado);
}
