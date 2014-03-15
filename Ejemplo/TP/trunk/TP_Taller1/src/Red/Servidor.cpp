/*
 * Servidor.cpp
 *
 *  Created on: 07/11/2013
 *  Last Amended: 11/11/2013
 *      Author: natuchis
 */

#include "Servidor.h"

#include "Log/Suceso.h"
#include "Red/base.h"
#include "Threads/Thread.h"

Servidor::Servidor()
	: fdEnt ()
	, fdSal ()
	, cantJugadores()
	, clientes ()
	, mutexCondicion ()
	, condicion(mutexCondicion)
	, canonico ()
	, deltas ()
{
}

Servidor::Servidor(int nroPuerto, Serializacion::Objeto canonicoInicial, size_t cantJugadores)
	: fdEnt (nroPuerto + 1)
	, fdSal (nroPuerto)
	, cantJugadores(cantJugadores)
	, clientes()
	, mutexCondicion ()
	, condicion(mutexCondicion)
	, canonico (canonicoInicial)
	, deltas ()
{
	fdSal.setKeepAlive();
	fdSal.setListen(4);
	fdEnt.setKeepAlive();
	fdEnt.setListen(4);

	// Inicio el thread de actualizaciones
	Threads::Thread("esperarActualizaciones", [&] () {
		while (true) {
			Serializacion::Objeto obj = deltas.pop();
			canonico.transform([&] (Serializacion::Objeto v) {
				return v.aplicar(obj);
			});
			broadcastDelta(std::move(obj));
			condicion.signal();
		}
		return 0;
	});

	// Inicio el thread para recibir clientes nuevos
	Threads::Thread esperarLlamada ("esperarLlamada", [&] () {
		while (true) {
			esperarLlamadas();
		}
		return 0;
	});
}

Servidor::~Servidor() {
	for (auto& par : clientes.get()) {
		close(par.second.fdEnt);
		close(par.second.fdSal);
	}
}

void Servidor::push (Serializacion::Objeto delta) {
	deltas.push(std::move(delta));
}

Serializacion::Objeto Servidor::getCanonico () {
	return canonico.get();
}

void Servidor::esperarLlamadas() {

	Red::Socket socketCliSal = fdEnt.aceptar();
	socketCliSal.setTimeoutRecibir(5, 0);

	Red::Socket socketCliEnt = fdSal.aceptar();

	if (estanTodosConectados()) {
		// Ya estan todos los jugadores conectados, rechazo el que recien se conecto
		enviarRechazo(socketCliEnt);
		Log::Suceso(Log::INFO, "Cliente rechazado por estar completa la cantidad de jugadores.");
		return;
	}

	Modelo::TipoJugador idCli;
	clientes.transform([&] (MapaClientes val) -> MapaClientes {
		idCli = getSiguienteJugador(val);
		val[idCli] = ParFD(socketCliEnt.extraerFd(), socketCliSal.extraerFd());
		return val;
	});

	// Envio el id del Jugador al cliente que recien se conecto
	enviarMensaje(idCli, Red::TipoMensaje::Jugador);

	// Envio el Objeto actual al cliente
	std::vector<uint8_t> vec = getCanonico().aRed();
	enviarMensaje(idCli, vec);

	Threads::Thread("esperarMensajes", [&] () {
		esperarMensajes(idCli);
		return 0;
	});
}

void Servidor::broadcastDelta(Serializacion::Objeto delta) {
	for (auto& par : clientes.get()) {
		try {
			enviarMensaje(par.first, delta.aRed());
		} catch (...) {
			desconectar(par.first);
		}
	}
}

size_t Servidor::cantClientes() const {
	return clientes.get().size();
}

bool Servidor::estanTodosConectados() const {
	return !(cantClientes() < cantJugadores);
}

void Servidor::esperarUsarDelta () {
	condicion.wait();
}

void Servidor::esperarMensajes(Modelo::TipoJugador idCli) {
	Red::TipoMensaje tipoMensaje;
	std::vector<uint8_t> datos;

	try {
		while (true) {
			if (!Red::recibir(getPar(idCli).fdSal, tipoMensaje, datos)) {
				desconectar(idCli);
				break;
			}
			switch (tipoMensaje) {
			case Red::TipoMensaje::Objeto:
				deltas.push(Serializacion::Objeto::deRed(datos));
				break;

			// Estos casos no se dan ya que los unicos msjs que puede recibir el servidor es de Objeto o Vivo
			case Red::TipoMensaje::Jugador:
			case Red::TipoMensaje::Rechazo:
			case Red::TipoMensaje::Vivo:
				// Al pasar un tiempo, el cliente manda un paquete para mantener vivo el socket
				// El servidor responde un vivo para mantener abierto el otro socket
				enviarMensaje(idCli, Red::TipoMensaje::Vivo);
				break;
			}
		}
	} catch (...) {
		desconectar(idCli);
	}
}

void Servidor::enviarMensaje(Modelo::TipoJugador idCli, std::vector<uint8_t> buffer) {
	if (!Red::enviar(getPar(idCli).fdEnt, Red::TipoMensaje::Objeto, buffer)) {
		desconectar(idCli);
	}
}

void Servidor::enviarRechazo(Red::Socket& fdCli) {
	std::vector<uint8_t> buffer;
	buffer.push_back(uint8_t(Red::TipoMensaje::Rechazo));
	fdCli.enviar(Red::TipoMensaje::Rechazo, buffer);
}

void Servidor::enviarMensaje(Modelo::TipoJugador idCli, Red::TipoMensaje tipoMensaje) {
	std::vector<uint8_t> buffer;
	buffer.push_back(uint8_t(idCli));
	if (!Red::enviar(getPar(idCli).fdEnt, tipoMensaje, buffer)) {
		desconectar(idCli);
	}
}

void Servidor::desconectar(Modelo::TipoJugador idCli) {
	ParFD eliminados;

	clientes.transform([&] (MapaClientes val) -> MapaClientes {
		if (val.count(idCli) != 0) {
			eliminados = val[idCli];
			val.erase(idCli);
		}
		return val;
	});

	close(eliminados.fdEnt);
	close(eliminados.fdSal);
	condicion.signal();
	std::string mensaje = "Desconectado cliente";
	Log::Suceso(Log::INFO, mensaje + Modelo::tipoJugadorToString(idCli));
}

Modelo::TipoJugador Servidor::getSiguienteJugador(MapaClientes val) {
	auto listaJugadores = Modelo::listaTipoJugador;
	listaJugadores.remove(Modelo::TipoJugador::Escenario);
	for (auto& jugador : listaJugadores) {
		if (val.count(jugador) == 0) {
			return jugador;
		}
	}
	throw Log::Suceso(Log::DEBUG, "Servidor busca otro jugador con 4 conectados.");
}

ParFD Servidor::getPar (Modelo::TipoJugador idCli) {
	return clientes.get().at(idCli);
}
