/*
 * Servidor.h
 *
 *  Created on: 07/11/2013
 *  Last Amended: 11/11/2013
 *      Author: natuchis
 */

#ifndef SERVIDOR_H_
#define SERVIDOR_H_

#include <map>
#include <vector>

#include "Modelo/TipoJugador.h"
#include "Red/ParFD.h"
#include "Red/Socket.h"
#include "Red/TipoMensaje.h"
#include "Serializacion/Interno/Objeto.h"
#include "Threads/Atomic.h"
#include "Threads/Queue.h"
#include "Threads/Thread.h"

class Servidor {
public:
	Servidor();
	Servidor(int nroPuerto, Serializacion::Objeto canonicoInicial, size_t cantJugadores);

	Servidor (const Servidor&) = delete;
	Servidor (Servidor&&) = default;
	Servidor& operator= (const Servidor&) = delete;
	Servidor& operator= (Servidor&&) = default;
	~Servidor();

	void push (Serializacion::Objeto delta);
	Serializacion::Objeto getCanonico ();

	void esperarLlamadas();
	size_t cantClientes() const;

	bool estanTodosConectados() const;
	void esperarUsarDelta ();

private:
	Red::Socket fdEnt;
	Red::Socket fdSal;

	size_t cantJugadores;

	// Lista de clientes conectados
	typedef std::map<Modelo::TipoJugador, ParFD> MapaClientes;
	Threads::Atomic<MapaClientes> clientes;

	Threads::Mutex mutexCondicion;
	Threads::Condition condicion;

	Threads::Atomic<Serializacion::Objeto> canonico;
	Threads::Queue<Serializacion::Objeto> deltas;

	Modelo::TipoJugador getSiguienteJugador(MapaClientes val);
	ParFD getPar (Modelo::TipoJugador idCli);
	void enviarMensaje(Modelo::TipoJugador idCli, Red::TipoMensaje tipoMensaje);
	void enviarRechazo(Red::Socket& fdCli);
	void broadcastDelta(Serializacion::Objeto delta);
	void enviarMensaje(Modelo::TipoJugador idCli, std::vector<uint8_t> buffer);
	void esperarMensajes(Modelo::TipoJugador idCli);
	void desconectar(Modelo::TipoJugador idCli);
};

#endif /* SERVIDOR_H_ */
