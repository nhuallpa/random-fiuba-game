#include "ModoSimulacion.h"

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

ModoSimulacion::ModoSimulacion ()
	: Visor()
	, sim(nullptr)
	, escenarioBackup()
	, ultimaSimulacion(0)
{
	proximoEstado = EstadoJuego::simulacion;
}

ModoSimulacion::ModoSimulacion (ModoEdicion&& origen)
	: Visor(std::move(origen))
	, sim(new simulador::Simulador(&juego->escenario.mundo))
	, escenarioBackup(juego->escenario.copiaProfunda())
	, ultimaSimulacion(0)
{
	proximoEstado = EstadoJuego::simulacion;
}

ModoSimulacion::~ModoSimulacion()
{
	delete sim;
}

EstadoJuego ModoSimulacion::estado ()
{
	return EstadoJuego::simulacion;
}

EstadoJuego ModoSimulacion::iteracionPrincipal (float ms)
{
	ultimaSimulacion += ms;
	if (ultimaSimulacion > float(1000)/simulador::Constantes::Instancia()->iteracionesPorSegundo) {
		sim->step();
		ultimaSimulacion -= float(1000)/simulador::Constantes::Instancia()->iteracionesPorSegundo;
	}

	return Visor::iteracionPrincipal(ms);
}

std::unique_ptr<ModoJuego> ModoSimulacion::transicion(EstadoJuego proximo)
{
	juego->escenario = escenarioBackup;
	return Visor::transicion(proximo);
}

} /* namespace Modo */
