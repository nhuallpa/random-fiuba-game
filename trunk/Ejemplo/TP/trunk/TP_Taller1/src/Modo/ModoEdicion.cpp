#include "ModoEdicion.h"

#include "Log/Suceso.h"
#include "Modelo/Juego.h"
#include "Modo/ModoSimulacion.h"
#include "Modo/Visor.h"
#include "Utils/make_unique.h"
#include "Vista/Botones/Guardar.h"
#include "Vista/Botones/Cargar.h"
#include "Vista/Botones/Salir.h"
#include "Vista/Botones/FlechaUp.h"
#include "Vista/Botones/FlechaDown.h"
#include "Vista/Canvas.h"
#include "Vista/Color.h"
#include "Vista/Contenedor.h"
#include "Vista/ContenedorLayout.h"
#include "Vista/FuentesPosicion/FuenteLayout.h"
#include "Vista/FuentesPosicion/FuenteVentana.h"
#include "Vista/Textbox.h"
#include "Vista/ToolBar.h"
#include "Vista/Ventana.h"

#include <map>

namespace Modo {


ModoEdicion::ModoEdicion ()
	: ModoJuego(nullptr)
	, juego(nullptr)
	, pathEscenario()
	, canvas(nullptr)
	, cambioModo(nullptr)
	, proximoEstado()
	, ultimoUpdate()
{
}

ModoEdicion::ModoEdicion (Ventana *ventana, Modelo::Juego *juego, std::string pathEscenario)
	: ModoJuego(ventana)
	, juego(juego)
	, pathEscenario(pathEscenario)
	, canvas(nullptr)
	, cambioModo(nullptr)
	, proximoEstado(EstadoJuego::edicion)
	, ultimoUpdate(0)
{
	// Creo el canvas con enlace al modelo
	FuenteLayout fuenteIzquierda;
	canvas = new Canvas(fuenteIzquierda, window, juego, Rect(0, 0, 20, 20));
	canvas->setBackground(juego->escenario.pathFondo, window);
	canvas->setPermitirEliminaciones(true);

	// Creo y agrego vistas al toolbar
	FuenteLayout fuenteDerecha;
	ContenedorLayout *derecha = new ContenedorLayout(fuenteDerecha, window, false);
	derecha->setSeparacion(0.02);

	vista::Color colorFondo;
	switch (juego->miJugador) {
	case Modelo::TipoJugador::Escenario:
		colorFondo = vista::Color(195, 195, 195);
		break;
	case Modelo::TipoJugador::Jugador1:
		colorFondo = vista::Color(195, 0, 0);
		break;
	case Modelo::TipoJugador::Jugador2:
		colorFondo = vista::Color(0, 0, 195);
		break;
	case Modelo::TipoJugador::Jugador3:
		colorFondo = vista::Color(0, 195, 0);
		break;
	case Modelo::TipoJugador::Jugador4:
		colorFondo = vista::Color(195, 195, 0);
		break;
	}
	derecha->setBackground(colorFondo, window);

	FuenteLayout fuenteCambio;
	cambioModo = new Boton(fuenteCambio,
		Imagen("imagenes/botones/play.png", window),
		[=, this] () {
			if (juego->miJugador == Modelo::TipoJugador::Escenario) {
				proximoEstado = EstadoJuego::simulacion;
			} else {
				proximoEstado = EstadoJuego::visor;
			}
		},
		"imagenes/botones/play.png",
		"imagenes/botones/play.png",
		false
	);
	derecha->addElemento(cambioModo);

	FuenteLayout fuenteToolbar;
	ToolBar *toolbar = new ToolBar(fuenteToolbar, window, canvas, juego);
	toolbar->setBackground(vista::Color(224, 224, 224), window);

	FuenteLayout fuenteBotonUp;
	Boton *botonUp = new FlechaUp(fuenteBotonUp, window, toolbar);
	derecha->addElemento(botonUp);

	derecha->addElemento(toolbar);

	FuenteLayout fuenteBotonDown;
	Boton *botonDown = new FlechaDown(fuenteBotonDown, window, toolbar);
	derecha->addElemento(botonDown);

	FuenteLayout fuenteArriba;
	ContenedorLayout* contenedorArriba = new ContenedorLayout(fuenteArriba, window, true);
	contenedorArriba->setSeparacion(0.05);
	contenedorArriba->setBackground(colorFondo, window);
	contenedorArriba->addElemento(canvas);
	contenedorArriba->addElemento(derecha);

	FuenteLayout fuenteSalir;
	Boton *salir = new Salir(fuenteSalir, window);

	FuenteVentana fuenteVentana(window);
	ContenedorLayout *contenedorVentana = new ContenedorLayout(fuenteVentana, window, false);
	contenedorVentana->setSeparacion(0.02);
	contenedorVentana->setBackground(colorFondo, window);
	contenedorVentana->addElemento(contenedorArriba);

	if (juego->miJugador == Modelo::TipoJugador::Escenario) {
		// Creo y agrego botones al contenedor
		FuenteLayout fuenteTextbox;
		Textbox *vistaTextbox = new Textbox(fuenteTextbox, window, juego->escenario.pathFondo);
		vistaTextbox->setRespuestaEnter([this, juego] (std::string texto) {
			juego->escenario.pathFondo = texto;
			canvas->setBackground(texto, window);
		});

		FuenteLayout fuenteCargar;
		Cargar *vistaCargar = new Cargar(fuenteCargar, window, vistaTextbox);

		FuenteLayout fuenteGuardar;
		Guardar *vistaGuardar = new Guardar(fuenteGuardar, window, juego, pathEscenario);

		FuenteLayout fuenteAbajo;
		ContenedorLayout *contenedorAbajo = new ContenedorLayout(fuenteAbajo, window, true);
		contenedorAbajo->setSeparacion(0.02);
		contenedorAbajo->setBackground(colorFondo, window);
		contenedorAbajo->addElemento(vistaTextbox);
		contenedorAbajo->addElemento(vistaCargar);
		contenedorAbajo->addElemento(vistaGuardar);
		contenedorAbajo->addElemento(salir);
		contenedorVentana->addElemento(contenedorAbajo, vista::PrioridadDibujo::barraAbajo);
	} else {
		derecha->addElemento(salir);
	}

	window->setRaiz(std::unique_ptr<Contenedor>(contenedorVentana));
}

ModoEdicion::~ModoEdicion()
{
}

EstadoJuego ModoEdicion::estado ()
{
	return EstadoJuego::edicion;
}

EstadoJuego ModoEdicion::iteracionPrincipal (float ms)
{
	ultimoUpdate += ms;
	if (ultimoUpdate > float(1000) / fps_deseado) {
		window->update();
		ultimoUpdate -= float(1000) / fps_deseado;
	}

	if (juego != nullptr) {
		auto par = window->getRaiz()->superficieAbsoluta(this->canvas);
		juego->jugadores[juego->miJugador].canvasAbsoluto = par.second;
	}

	return proximoEstado;
}

std::unique_ptr<ModoJuego> ModoEdicion::transicion(EstadoJuego proximo)
{
	switch (proximo) {
	case EstadoJuego::simulacion:
		return make_unique<ModoSimulacion>(std::move(*this));
	case EstadoJuego::visor:
		return make_unique<Visor>(std::move(*this));
	default:
		throw Log::Suceso(Log::DEBUG, "Cambio de modo invalido");
	}
}

} /* namespace Modo */
