#include "FuenteVentana.h"

#include "Vista/Ventana.h"
#include "Utils/Vec2.h"
#include "Utils/Rect.h"

FuenteVentana::FuenteVentana (Ventana *ventana)
	: ventana(ventana)
{
}

FuenteVentana::FuenteVentana (const FuenteVentana& rhs)
	: ventana(rhs.ventana)
{
}

FuenteVentana::~FuenteVentana ()
{
}

Rect FuenteVentana::getSuperficie () const
{
	return Rect(Vec2(0, 0), ventana->tamDibujo());
}

void FuenteVentana::setSuperficie (const Rect&)
{
}

Vec2 FuenteVentana::getTamPadre () const
{
	return ventana->tamDibujo();
}

void FuenteVentana::padreResizeado (Vec2)
{
}

float FuenteVentana::getAngulo () const
{
	return 0;
}

void FuenteVentana::setAngulo (float)
{
}

bool FuenteVentana::getEstadoNormal () const
{
	return true;
}

void FuenteVentana::setEstadoNormal (bool)
{
}

FuentePosicion *FuenteVentana::clonar() const {
	return new FuenteVentana(*this);
}
