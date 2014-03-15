/*
 * Mision.cpp
 *
 *  Created on: 04/12/2013
 *  Last Amended: 04/12/2013
 *      Author: natuchis
 */

#include "Mision.h"

Mision::Mision(const FuentePosicion& unaFuente, Dibujable* unDestino, std::string mensaje, bool *aviso)
	: Boton(unaFuente
		, Imagen(mensaje, unDestino)
		, [aviso] { *aviso = true; }
		, mensaje
		, mensaje
		, false)
{
}

Mision::~Mision() {
}

