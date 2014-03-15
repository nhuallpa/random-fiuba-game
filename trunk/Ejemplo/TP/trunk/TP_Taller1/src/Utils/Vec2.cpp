#include "Vec2.h"

#include "Rect.h"
#include <Box2D/Common/b2Math.h>
#include <string>
#include <cmath>

Vec2::Vec2 (float xy)
	: x(xy)
	, y(xy)
{
}

Vec2 polar (float r, float a)
{
	return Vec2(r * cos(a), r * sin(a));
}

bool Vec2::operator== (const Vec2& rhs) const
{
	return this->x == rhs.x && this->y == rhs.y;
}

bool Vec2::operator!= (const Vec2& rhs) const
{
	return this->x != rhs.x || this->y != rhs.y;
}

Vec2 Vec2::operator* (float rhs) const
{
	return Vec2(x * rhs, y * rhs);
}

Vec2 Vec2::operator* (const Vec2& rhs) const
{
	return Vec2(x * rhs.x, y * rhs.y);
}

Vec2 Vec2::operator- () const
{
	return Vec2(-x, -y);
}

Vec2 Vec2::operator/ (float rhs) const
{
	return Vec2(x/rhs, y/rhs);
}

Vec2 Vec2::operator/ (const Vec2& rhs) const
{
	return Vec2(x / rhs.x, y / rhs.y);
}

Vec2& Vec2::operator+= (const Vec2& rhs)
{
	*this = *this + rhs;
	return *this;
}

Vec2& Vec2::operator-= (const Vec2& rhs)
{
	*this = *this - rhs;
	return *this;
}

Vec2& Vec2::operator*= (float rhs)
{
	*this = *this * rhs;
	return *this;
}

Vec2& Vec2::operator/= (float rhs)
{
	*this = *this / rhs;
	return *this;
}

Vec2& Vec2::operator*= (const Vec2& rhs)
{
	*this = *this * rhs;
	return *this;
}

Vec2& Vec2::operator/= (const Vec2& rhs)
{
	*this = *this / rhs;
	return *this;
}

Vec2 Vec2::cambioCoordenadas (const Rect& sistOrigen, const Rect& sistDestino) const
{
	Vec2 relOrigen(*this - sistOrigen.origen());
	Vec2 relDestino(relOrigen * sistDestino.tam() / sistOrigen.tam());
	return relDestino + sistDestino.origen();
}

Vec2 Vec2::rotar (float deg) const
{
	float rad = M_PI * deg / 180;
	return Vec2(x * cos(rad) + y * sin(rad), x * sin(rad) - y * cos(rad));
}

float Vec2::abs () const
{
	return sqrt(x*x + y*y);
}

float Vec2::distancia (Vec2 punto) const
{
	return (*this - punto).abs();
}

float Vec2::angulo () const
{
	return atan2(y, x) * 180 / M_PI;
}

float Vec2::anguloCon (Vec2 punto) const
{
	return (*this - punto).angulo();
}

Vec2::Vec2 (b2Vec2 base)
	: x(base.x)
	, y(base.y)
{
}

Vec2::operator b2Vec2 () const
{
	return b2Vec2(x, y);
}
