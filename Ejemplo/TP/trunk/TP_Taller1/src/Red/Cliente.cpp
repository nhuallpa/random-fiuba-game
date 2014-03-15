/*
 * Cliente.cpp
 *
 *  Created on: 07/11/2013
 *  Last Amended: 11/11/2013
 *      Author: natuchis
 */

#include "Cliente.h"

Cliente::Cliente()
	: fdEnt()
	, fdSal()
	, idJugador(Modelo::TipoJugador::Escenario)
	, timeInicial()
	, threadEsperarMensajes()
	, threadVerificarVida()
	, canonico()
	, deltasRed()
	, deltasLocal()
{
}

Cliente::Cliente(int nroPuerto, char* hostName)
	: fdEnt(Red::Socket::crear())
	, fdSal(Red::Socket::crear())
	, idJugador(Modelo::TipoJugador::Escenario)
	, timeInicial(time(NULL))
	, threadEsperarMensajes()
	, threadVerificarVida()
	, canonico()
	, deltasRed()
	, deltasLocal()
{
	fdEnt.setKeepAlive();
	fdEnt.setTimeoutRecibir(5, 0);
	fdSal.setKeepAlive();
	fdSal.setTimeoutEnviar(5, 0);

	fdEnt.conectar(hostName, nroPuerto);
	fdSal.conectar(hostName, nroPuerto + 1);

	esperarMensaje(); // recibo id jugador o rechazo
	esperarMensaje(); // recibo objeto inicial

	threadEsperarMensajes = Threads::Thread("esperarMensajes", [&] () {
		while (vivo()) {
			esperarMensaje();
		}
		return 0;
	});

	Threads::Thread("esperarActualizacionesRed", [&] () {
		while (vivo()) {
			Serializacion::Objeto delta = deltasRed.pop();
			canonico.transform([&] (Serializacion::Objeto obj) {
				return obj.aplicar(std::move(delta));
			});
		}
		return 0;
	});

	Threads::Thread("esperarActualizacionesLocal", [&] () {
		while (vivo()) {
			Serializacion::Objeto delta = deltasLocal.pop();
			enviarMensaje(Red::TipoMensaje::Objeto, delta.aRed());
		}
		return 0;
	});

	threadVerificarVida = Threads::Thread("verificarVida", [&] () {
		while (vivo()) {
			time_t timeFinal = time(NULL);
			// TODO Configurar bien el tiempo
			if (timeFinal - timeInicial > 2) {
				std::vector<uint8_t> basura;
				basura.push_back(uint8_t(idJugador));
				enviarMensaje(Red::TipoMensaje::Vivo, basura);
				Log::Suceso(Log::INFO, "Se envio vivo");
			}
			// TODO Configurar bien el tiempo
			sleep(1);
		}
		return 0;
	});
}

Cliente::~Cliente() {
}

void Cliente::esperarMensaje() {
	Red::TipoMensaje tipo;
	std::vector<uint8_t> datos;
	if (!fdEnt.recibir(tipo, datos)) {
		throw Log::Suceso(Log::FATAL, "Corte en la conexion.");
	}

	switch (tipo) {
	case Red::TipoMensaje::Jugador:
		idJugador = Modelo::TipoJugador(datos[0]);
		break;

	case Red::TipoMensaje::Objeto:
		deltasRed.push(Serializacion::Objeto::deRed(datos));
		break;

	case Red::TipoMensaje::Rechazo:
		throw Log::Suceso(Log::FATAL, "Servidor rechazo la conexion.");
		break;

	case Red::TipoMensaje::Vivo:
		break;
	}
}

bool Cliente::vivo () {
	return !threadEsperarMensajes.termino() || threadVerificarVida.termino();
}

void Cliente::push (Serializacion::Objeto delta) {
	deltasLocal.push(std::move(delta));
}

Serializacion::Objeto Cliente::getCanonico () {
	return canonico.get();
}

void Cliente::enviarMensaje(Red::TipoMensaje tipoMensaje, std::vector<uint8_t> buffer) {
	if (!fdSal.enviar(tipoMensaje, std::move(buffer))) {
		throw Log::Suceso(Log::FATAL, "Corte en la conexion.");
	}
	timeInicial = time(NULL);
}

Modelo::TipoJugador Cliente::getTipoJugador() {
	return idJugador;
}
