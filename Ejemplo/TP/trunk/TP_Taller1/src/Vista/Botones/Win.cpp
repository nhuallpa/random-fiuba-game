/*
 * Win.cpp
 *
 *  Created on: 04/12/2013
 *  Last Amended: 04/12/2013
 *      Author: natuchis
 */

#include "Win.h"

Win::Win(const FuentePosicion& unaFuente, Dibujable* unDestino, bool* aviso)
		: Boton(unaFuente
		, Imagen("imagenes/mensajes/win.png", unDestino)
		, [aviso] { *aviso = true; }
		, "imagenes/mensajes/win.png"
		, "imagenes/mensajes/win.png"
		, false)
{
}

Win::~Win() {
}

