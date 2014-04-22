///*
// * Cliente.h
// *
// *  Created on: 07/11/2013
// *  Last Amended: 11/11/2013
// *      Author: natuchis
// */
//
//#ifndef CLIENTE_H_
//#define CLIENTE_H_
//
//#include "Modelo/TipoJugador.h"
//#include "Red/Socket.h"
//#include "Red/TipoMensaje.h"
//#include "Serializacion/Interno/Objeto.h"
//#include "Threads/Atomic.h"
//#include "Threads/Queue.h"
//#include "Threads/Thread.h"
//#include <string>
//#include <vector>
//
//class Cliente {
//public:
//	Cliente();
//	Cliente(int nroPuerto, char* hostName);
//	~Cliente();
//
//	bool vivo ();
//
//	void push (Serializacion::Objeto delta);
//	Serializacion::Objeto getCanonico ();
//
//	Modelo::TipoJugador getTipoJugador();
//
//private:
//	Red::Socket fdEnt;
//	Red::Socket fdSal;
//	Modelo::TipoJugador idJugador;
//
//	// Se usa para controlar el timeout de los sockets
//	time_t timeInicial;
//
//	Threads::Thread threadEsperarMensajes;
//	Threads::Thread threadVerificarVida;
//
//	Threads::Atomic<Serializacion::Objeto> canonico;
//	Threads::Queue<Serializacion::Objeto> deltasRed;
//	Threads::Queue<Serializacion::Objeto> deltasLocal;
//
//	void esperarMensaje();
//	void enviarMensaje(Red::TipoMensaje tipoMensaje, std::vector<uint8_t> buffer);
//};
//
//#endif /* CLIENTE_H_ */
