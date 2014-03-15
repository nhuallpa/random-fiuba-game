#include "FuenteLayout.h"

FuenteLayout::FuenteLayout (const Vec2& tamPadre)
	: tamPadre(tamPadre)
	, superficie(Vec2(), tamPadre)
{
}

FuenteLayout::FuenteLayout (const FuenteLayout& rhs)
	: tamPadre(rhs.tamPadre)
	, superficie(Vec2(), rhs.tamPadre)
{
}

FuenteLayout::~FuenteLayout ()
{
}

Rect FuenteLayout::getSuperficie () const
{
	return superficie;
}

void FuenteLayout::setSuperficie (const Rect& nSuperficie)
{
	superficie = nSuperficie;
}

Vec2 FuenteLayout::getTamPadre () const
{
	return tamPadre;
}

void FuenteLayout::padreResizeado (Vec2 nTam)
{
	tamPadre = nTam;
}

float FuenteLayout::getAngulo () const
{
	return 0;
}

void FuenteLayout::setAngulo (float)
{
}

bool FuenteLayout::getEstadoNormal () const
{
	return true;
}

void FuenteLayout::setEstadoNormal (bool)
{
}

FuentePosicion *FuenteLayout::clonar() const {
	return new FuenteLayout(*this);
}
