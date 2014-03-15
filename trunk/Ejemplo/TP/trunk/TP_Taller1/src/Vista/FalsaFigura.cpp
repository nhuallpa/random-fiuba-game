#include "FalsaFigura.h"

#include "Utils/make_unique.h"
#include "Vista/ClickInfo.h"
#include "Vista/InfoFiguras.h"
#include "Vista/LayoutInfo.h"
#include "Vista/Texto.h"
#include "Vista/FuentesPosicion/FuenteFuncion.h"

namespace vista {

FalsaFigura::FalsaFigura (const FuentePosicion& fuente, Modelo::TipoElemento tipo, Dibujable *dib, size_t cantidad)
	: Elemento(fuente)
	, tipo(tipo)
	, imagen(InfoFiguras::datos[tipo].pathImagenToolbar, dib)
	, numero(dib, std::to_string(cantidad))
	, real()
	, cantidad(cantidad)
{
	FuenteFuncion fuenteReal(
		[this, tipo] () -> Rect {
			Rect base = this->fuente->getSuperficie();
			base.setTam(base.tam() * InfoFiguras::datos[tipo].tamCanvas);
			return std::move(base);},
		[this, tipo] () -> float {
			return this->fuente->getAngulo() + InfoFiguras::datos[tipo].anguloCanvas;},
		[this] () -> bool {
			return this->fuente->getEstadoNormal();},
		[this] () -> Vec2 {
			return this->fuente->getTamPadre();});
	real = FiguraVista(tipo, fuenteReal, dib);
}

FalsaFigura::~FalsaFigura ()
{
}

void FalsaFigura::setSuperfice (const Rect& val)
{
	fuente->setSuperficie(val);
}

void FalsaFigura::dibujarse (DestinoDibujo* window)
{
	imagen.dibujar(*window, *fuente);

	Vec2 tam = numero.tamDibujo();
	Vec2 origen = fuente->getSuperficie().origen() + fuente->getSuperficie().tam() * Vec2(0, 1);
	numero.dibujarse(window, Rect(origen, tam), fuente->getTamPadre());
}

bool FalsaFigura::dirty ()
{
	return true;
}

LayoutInfo FalsaFigura::getLayoutInfo ()
{
	return LayoutInfo(imagen.tamDibujo());
}

ClickInfo FalsaFigura::recibirClick (Vec2 pos)
{
	if (cantidad == 0) {
		return ClickInfo();
	}
	auto retval = real.recibirClick(pos);
	retval.puedeResizear = false;
	retval.puedeRotar = false;
	retval.puedeUnirse = false;
	retval.esCanvas = false;
	return retval;
}

Elemento* FalsaFigura::clonar () const
{
	return real.clonar();
}

Modelo::TipoElemento FalsaFigura::getTipo () const
{
	return tipo;
}

void FalsaFigura::setCantidad (size_t nCantidad)
{
	if (cantidad != nCantidad) {
		cantidad = nCantidad;
		numero.setTexto(std::to_string(nCantidad));
	}
}

} /* namespace vista */
