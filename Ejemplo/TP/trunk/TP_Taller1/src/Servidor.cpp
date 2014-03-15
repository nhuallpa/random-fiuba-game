/*
 * Servidor.cpp
 *
 *  Created on: 06/11/2013
 *  Last Amended: 11/11/2013
 *      Author: natuchis
 */

#include "Red/Servidor.h"
#include "Simulador/Constantes.h"
#include "Log/Suceso.h"
#include "Log/Logger.h"
#include "Modelo/Juego.h"
#include "Threads/Thread.h"
#include "Threads/Queue.h"
#include "Serializacion/Escenario.h"
#include "Serializacion/Juego.h"
#include "Serializacion/YAML/archivo.h"
#include "Simulador/Simulador.h"
#include "Sonido/Sonido.h"
#include <SDL2/SDL_timer.h>


static bool puedeSimular (Servidor *server, Modelo::Juego *juego)
{
	if (!server->estanTodosConectados()) {
		return false;
	}
	for (auto& parJugador : juego->jugadores) {
		if (parJugador.second.modoJuegoActual != Modo::EstadoJuego::visor) {
			return false;
		}
	}
	return true;
}


static void mainSimulacion (Servidor *server, Modelo::Juego *juego)
{
	Escenario escenarioBackup = juego->escenario.copiaProfunda();
	float ultimaSimulacion = 0;
	simulador::Simulador sim(&juego->escenario.mundo);

	try {
		// Seteo y propago que no verifique colisiones
		{
			Modelo::Juego setter = *juego;
			setter.escenario.mundo.validaColisiones() = false;
			setter.simulando = true;
			server->push(Serializacion::Objeto(*juego).diferencia( std::move(setter) ));
		}

		Sonido::Instancia()->setJuego(juego);
		Sonido::Instancia()->setSalida(Salida::red);

		while (puedeSimular(server, juego)) {
			unsigned inicio = SDL_GetTicks();
			if (ultimaSimulacion > float(1000)/simulador::Constantes::Instancia()->iteracionesPorSegundo) {
				auto preSimulacion = server->getCanonico();
				juego->asignacionProfunda(preSimulacion);
				ultimaSimulacion -= float(1000)/simulador::Constantes::Instancia()->iteracionesPorSegundo;
				sim.step();
				server->push(preSimulacion.diferencia(*juego));
				Sonido::Instancia()->actualizar();
			} else {
				usleep(500);
			}
			ultimaSimulacion += SDL_GetTicks() - inicio;
			server->esperarUsarDelta();
		}
	} catch (...) {}

	juego->escenario.asignacionProfunda(std::move(escenarioBackup));
	server->push(server->getCanonico().diferencia(*juego));
}


int main(int argc, char** argv) {
	// Creo los logger
	Log::Logger cout_logger(Log::FATAL | Log::ERROR | Log::DEBUG);
	Log::Logger file_logger("LogServidor.txt", Log::ALL);

	if (argc != 3) {
		Log::Suceso(Log::FATAL, "Cantidad de argumentos invalido. \n Ingreso correcto: Servidor <Numero de Puerto> <path de archivo YAML>");
		return -1;
	}

	int nroPuerto = atoi(argv[1]);
	if (nroPuerto > 65534 || nroPuerto < 1024) {
		Log::Suceso(Log::FATAL, "Numero de puerto incorrecto. Ingrese un puerto: [1024,65534].");
		return -2;
	}

	Serializacion::Objeto inicial = YAML_leerArchivo(argv[2]);
	Modelo::Juego juego(inicial);

	if (juego.jugadores.size() == 0) {
		Log::Suceso(Log::FATAL, "Intento crear servidor sin jugadores.");
		return -4;
	}

	Servidor *server;
	try {
		server = new Servidor(nroPuerto, inicial, juego.jugadores.size());
	} catch (...) {
		Log::Suceso(Log::FATAL, "No se pudo establecer el servidor.");
		return -3;
	}
	Sonido::Instancia()->setJuego(&juego);
	Sonido::Instancia()->setSalida(Salida::red);

	while (true) {
		if (server->estanTodosConectados()) {
			juego = server->getCanonico();
			if (puedeSimular(server, &juego)) {
				mainSimulacion(server, &juego);
			}
			Sonido::Instancia()->actualizar();
			SDL_Delay(50);
		}
		SDL_Delay(100);
	}

	return 0;
}
