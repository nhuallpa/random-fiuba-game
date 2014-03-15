#include "FuenteFuncion.h"

FuenteFuncion::FuenteFuncion(std::function<Rect()> sup,
                             std::function<float()> angulo,
                             std::function<bool()> estadoNormal,
                             std::function<Vec2()> padre)
	: sup(sup)
	, angulo(angulo)
	, estadoNormal(estadoNormal)
	, padre(padre)
{
}

FuenteFuncion::FuenteFuncion (const FuenteFuncion& rhs)
	: sup(rhs.sup)
	, angulo(rhs.angulo)
	, estadoNormal(rhs.estadoNormal)
	, padre(rhs.padre)
{
}

FuenteFuncion::~FuenteFuncion()
{
}

Rect FuenteFuncion::getSuperficie () const
{
	return sup();
}

void FuenteFuncion::setSuperficie (const Rect&)
{
}

Vec2 FuenteFuncion::getTamPadre () const
{
	return padre();
}

void FuenteFuncion::padreResizeado (Vec2)
{
}

float FuenteFuncion::getAngulo () const
{
	return angulo();
}

void FuenteFuncion::setAngulo (float)
{
}

bool FuenteFuncion::getEstadoNormal () const
{
	return estadoNormal();
}

void FuenteFuncion::setEstadoNormal (bool)
{
}

FuentePosicion* FuenteFuncion::clonar() const
{
	return new FuenteFuncion(*this);
}
