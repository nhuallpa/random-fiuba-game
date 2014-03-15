#include "Visor.h"

#include "Log/Suceso.h"
#include "Modelo/Juego.h"
#include "Modo/ModoEdicion.h"
#include "Simulador/Constantes.h"
#include "Simulador/Simulador.h"
#include "Utils/make_unique.h"
#include "Vista/Boton.h"
#include "Vista/Contenedor.h"
#include "Vista/Imagen.h"
#include "Vista/Ventana.h"
#include "Vista/Botones/Salir.h"
#include "Vista/FuentesPosicion/FuentePosicion.h"
#include "Vista/FuentesPosicion/FuenteFuncion.h"
#include <utility>

namespace Modo {

Visor::Visor ()
	: ModoJuego(nullptr)
	, juego(nullptr)
	, pathEscenario()
	, canvas(nullptr)
	, cambioModo(nullptr)
	, proximoEstado(EstadoJuego::visor)
	, ultimoGrafico(0)
{
}

Visor::Visor (ModoEdicion&& origen)
	: ModoJuego(origen.window)
	, juego(origen.juego)
	, pathEscenario(std::move(origen.pathEscenario))
	, canvas(origen.canvas)
	, cambioModo(origen.cambioModo)
	, proximoEstado(EstadoJuego::visor)
	, ultimoGrafico(0)
{
	*cambioModo = Boton(*cambioModo->getFuente(),
		Imagen("imagenes/botones/stop.png", window),
		[&proximoEstado] () {
			proximoEstado = EstadoJuego::edicion;
		},
		"imagenes/botones/stop.png",
		"imagenes/botones/stop.png",
		false
	);
}

Visor::~Visor()
{
}

EstadoJuego Visor::estado ()
{
	return EstadoJuego::visor;
}

EstadoJuego Visor::iteracionPrincipal (float ms)
{
	ultimoGrafico += ms;
	if (ultimoGrafico > float(1000)/fps_deseado) {
		window->update();
		ultimoGrafico -= float(1000)/fps_deseado;
	}

	return proximoEstado;
}

std::unique_ptr<ModoJuego> Visor::transicion(EstadoJuego proximo)
{
	switch (proximo) {
	case EstadoJuego::edicion:
		return make_unique<ModoEdicion>(window, juego, pathEscenario);
	default:
		throw Log::Suceso(Log::DEBUG, "Cambio de modo invalido");
	}
}

} /* namespace Modo */
