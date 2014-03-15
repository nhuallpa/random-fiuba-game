#include "Elemento.h"

#include "Vista/ClickInfo.h"
#include "Vista/FuentesPosicion/FuentePosicion.h"
#include "Utils/Rect.h"

#include <utility>

namespace vista {

Elemento::Elemento ()
	: visible(true)
	, fuente(nullptr)
{
}

Elemento::Elemento (const FuentePosicion& nFuente)
	: visible(true)
	, fuente(nFuente.clonar())
{
}

Elemento::Elemento (const Elemento& base)
	: visible(true)
	, fuente(nullptr)
{
	if (base.fuente != nullptr) {
		fuente.reset(base.fuente->clonar());
	}
}

Elemento& Elemento::operator= (const Elemento& base)
{
	this->fuente = std::unique_ptr<FuentePosicion>(base.fuente->clonar());
	this->visible = base.visible;
	return *this;
}

Elemento::~Elemento()
{
}

void Elemento::ocultar()
{
	visible = false;
}

void Elemento::mostrar()
{
	visible = true;
}

bool Elemento::visibilidad()
{
	return visible;
}

bool Elemento::contiene(Vec2 punto)
{
	return this->getSuperficie().contiene(punto);
}

ClickInfo Elemento::recibirClick(Vec2)
{
	return ClickInfo();
}

bool Elemento::aEliminar (Vec2)
{
	return false;
}

Rect Elemento::getSuperficie() const
{
	return fuente->getSuperficie();
}

FuentePosicion* Elemento::getFuente () const
{
	return fuente.get();
}

void Elemento::setFuente(FuentePosicion* nFuente)
{
	fuente.reset(nFuente);
}

bool Elemento::dirty()
{
	return true;
}

bool Elemento::recibirFigura (const FiguraVista*, Vec2, vista::PrioridadDibujo)
{
	return false;
}

bool Elemento::recibirElementoPuente(FiguraVista *elemento, Vec2 extremoA,
		Vec2 extremoB, vista::PrioridadDibujo prioridad) {
	return false;
}

std::pair<bool,Rect> Elemento::superficieAbsoluta (Elemento *elemento)
{
	if (this == elemento) {
		return std::make_pair(true, fuente->getSuperficie());
	}
	return std::make_pair(false, Rect());
}

bool Elemento::accionarElementos(FiguraVista* fig, Vec2 pos, Modelo::TipoAccion accion)
{
	return false;
}

Elemento* Elemento::clonar() const
{
	return nullptr;
}

} /* namespace vista */
