#include "Aviso.h"

#include "Log/Suceso.h"
#include "Utils/make_unique.h"
#include "Vista/Color.h"
#include "Vista/Textura.h"
#include "Vista/Ventana.h"
#include "Vista/Botones/Win.h"
#include "Vista/Botones/Error.h"
#include "Vista/Botones/Mision.h"
#include "Vista/FuentesPosicion/FuenteVentana.h"
#include "Vista/FuentesPosicion/FuenteFuncion.h"

namespace Modo {

Aviso::Aviso ()
	: ModoJuego(nullptr)
	, contenedorVentana()
	, anterior()
	, tipoAviso()
	, mensaje()
	, aceptado_()
{
}

Aviso::Aviso (std::unique_ptr<ModoJuego> anterior, TipoAviso tipo, std::string mensaje)
	: ModoJuego(anterior->window)
	, contenedorVentana(anterior->window->extraerRaiz())
	, anterior(std::move(anterior))
	, tipoAviso(tipo)
	, mensaje(mensaje)
	, aceptado_(false)
{
	auto fondo = make_unique<Textura>(*window, window->tamDibujo());
	contenedorVentana->dibujarse(fondo.get());
	// Oscurezco el fondo del juego
	fondo.get()->mezclar(vista::Color(0,0,0,60));

	// Seteo el escenario oscurecido como fondo
	FuenteVentana fuenteAviso(window);
	Contenedor *contenedorAviso = new Contenedor(fuenteAviso, window);
	contenedorAviso->setBackground(std::move(fondo));

	FuenteFuncion fuente(
		[&, tipoAviso] () -> Rect {
			return Rect::deCentro(contenedorVentana->getSuperficie().centro(),
					      getTamanio(tipoAviso));},
		[] () -> float {
			return 0;},
		[] () -> bool {
			return true;},
		[&] () -> Vec2 {
			return window->tamDibujo();});
	Boton *boton;
	switch (tipoAviso) {
		case TipoAviso::Win:
			boton = new Win(fuente, window, &aceptado_);
			break;

		case TipoAviso::Error:
			boton = new Error(fuente, window, mensaje);
			break;

		case TipoAviso::Mision:
			boton = new Mision(fuente, window, mensaje, &aceptado_);
			break;
	}

	contenedorAviso->addElemento(boton, vista::PrioridadDibujo::arrastrando);

	window->setRaiz(std::unique_ptr<Contenedor>(contenedorAviso));
	window->update();
}

Aviso::~Aviso()
{
}

EstadoJuego Aviso::estado ()
{
	return EstadoJuego::aviso;
}

EstadoJuego Aviso::iteracionPrincipal (float ms)
{
	window->update();
	if (aceptado_) {
		return anterior->estado();
	} else {
		return estado();
	}
}

std::unique_ptr<ModoJuego> Aviso::transicion(EstadoJuego proximo)
{
	if (proximo != anterior->estado()) {
		throw Log::Suceso(Log::DEBUG, "Cambio de modo invalido");
	}
	window->setRaiz(std::move(contenedorVentana));
	window->update();
	return std::move(anterior);
}

Vec2 Aviso::getTamanio (TipoAviso tipoAviso)
{
	Vec2 retorno;
	switch (tipoAviso) {
		case TipoAviso::Win:
			retorno = Vec2(240 * 1.1, 171 * 1.1);
			break;
		case TipoAviso::Error:
		case TipoAviso::Mision:
			retorno = Vec2(208, 226);
			break;
	}
	return retorno;
}

} /* namespace Modo */
