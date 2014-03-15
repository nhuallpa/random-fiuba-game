/*
 * Error.cpp
 *
 *  Created on: 04/12/2013
 *  Last Amended: 04/12/2013
 *      Author: natuchis
 */

#include "Error.h"

Error::Error(const FuentePosicion& unaFuente, Dibujable* unDestino, std::string mensaje)
	: Boton(unaFuente
	       , Imagen("imagenes/mensajes/error.png", unDestino)
	       , [] {}
	       , "imagenes/mensajes/error.png"
	       , "imagenes/mensajes/error.png"
	       , false)
{
}

Error::~Error() {
}

