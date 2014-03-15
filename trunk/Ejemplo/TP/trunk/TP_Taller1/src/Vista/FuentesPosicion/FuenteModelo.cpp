#include "FuenteModelo.h"

#include "Utils/Rect.h"
#include "Vista/Canvas.h"

FuenteModelo::FuenteModelo (Modelo::EntidadWrapper entidad, Canvas *canvas)
	: entidad(entidad)
	, canvas(canvas)
{
}

FuenteModelo::~FuenteModelo ()
{
}

Rect FuenteModelo::getSuperficie () const
{
	try {
		Rect sup(Rect::deCentro(entidad.centro(), entidad.tamanio()));
		return sup.cambioCoordenadas(canvas->getRegionModelo(), Rect(Vec2(), canvas->getSuperficie().tam()));
	} catch (...) {
		return Rect(-100, -100, 10, 10);
	}
}

void FuenteModelo::setSuperficie (const Rect& val)
{
	Rect sup = val.cambioCoordenadas(Rect(Vec2(), canvas->getSuperficie().tam()), canvas->getRegionModelo());

	entidad.centro() = sup.centro();
	entidad.tamanio() = sup.tam();
}

Vec2 FuenteModelo::getTamPadre () const
{
	return canvas->getSuperficie().tam();
}

void FuenteModelo::padreResizeado (Vec2)
{
}

float FuenteModelo::getAngulo () const
{
	try {
		return entidad.angulo();
	} catch (...) {
		return 0;
	}
}

void FuenteModelo::setAngulo (float val)
{
	entidad.angulo() = val;
}

bool FuenteModelo::getEstadoNormal () const
{
	try {
		return entidad.estadoNormal();
	} catch (...) {
		return true;
	}
}

void FuenteModelo::setEstadoNormal (bool val)
{
	entidad.estadoNormal() = val;
}

Modelo::EntidadWrapper FuenteModelo::getEntidad()
{
	return entidad;
}

FuentePosicion *FuenteModelo::clonar() const {
	return new FuenteModelo(*this);
}
