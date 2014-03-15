/*
 * Cliente.cpp
 *
 *  Created on: 06/11/2013
 *  Last Amended: 11/11/2013
 *      Author: natuchis
 */

#include "Main/mainJuego.h"

#include "Log/Suceso.h"
#include "Log/Logger.h"
#include "Red/Cliente.h"
#include "Sonido/Sonido.h"

int main(int argc, char** argv)
{
	//Creo los logger
	Log::Logger cout_logger(Log::FATAL | Log::ERROR | Log::DEBUG);
	Log::Logger file_logger("LogCliente.txt", Log::ALL);

	if (argc != 3) {
		Log::Suceso(Log::FATAL, "Cantidad de argumentos invalido. \n Ingreso correcto: Cliente <Numero de Puerto> <HostName>");
		return -1;
	}

	int nroPuerto = atoi(argv[1]);
	if (nroPuerto > 65534 || nroPuerto < 1024) {
		Log::Suceso(Log::FATAL, "Numero de puerto incorrecto. Ingrese un puerto: [1024,65534].");
		return -2;
	}
	Cliente *cliente;
	try {
		cliente = new Cliente(nroPuerto, argv[2]);
	} catch (...) {
		Log::Suceso(Log::FATAL, "No se pudo establecer cliente.");
		return -3;
	}
	Sonido::Instancia()->setSalida(Salida::local);
	return mainJuego(cliente, "salidaCliente.yaml");
}
