#include "FuenteMouse.h"

#include "Controlador/Mouse.h"
#include "Vista/Ventana.h"

FuenteMouse::FuenteMouse()
	: superficieBase()
	, angulo()
	, estadoNormal()
	, ventana()
	, mouse()
{}

FuenteMouse::FuenteMouse (const Ventana *ventana, const controlador::Mouse *mouse,
                          FuentePosicion* fuenteVieja)
	: superficieBase()
	, angulo(fuenteVieja->getAngulo())
	, estadoNormal(fuenteVieja->getEstadoNormal())
	, ventana(ventana)
	, mouse(mouse)
{
	superficieBase.setTam(fuenteVieja->getSuperficie().tam());
	superficieBase.setCentro(Vec2());
}

FuenteMouse::FuenteMouse (const FuenteMouse &rhs)
	: superficieBase(rhs.superficieBase)
	, angulo(rhs.angulo)
	, estadoNormal(rhs.estadoNormal)
	, ventana(rhs.ventana)
	, mouse(rhs.mouse)
{
}

FuenteMouse::~FuenteMouse ()
{
}

Rect FuenteMouse::getSuperficie () const
{
	if (mouse != NULL) {
		return superficieBase + mouse->getPosicionMouse();
	} else {
		return superficieBase;
	}
}

void FuenteMouse::setSuperficie (const Rect&)
{
}

Vec2 FuenteMouse::getTamPadre () const
{
	return ventana->tamDibujo();
}

void FuenteMouse::padreResizeado (Vec2)
{
}

float FuenteMouse::getAngulo () const
{
	return angulo;
}

void FuenteMouse::setAngulo (float nAngulo)
{
	angulo = nAngulo;
}

bool FuenteMouse::getEstadoNormal () const
{
	return estadoNormal;
}

void FuenteMouse::setEstadoNormal (bool nEstado)
{
	estadoNormal = nEstado;
}

FuentePosicion* FuenteMouse::clonar() const
{
	return new FuenteMouse(*this);
}
