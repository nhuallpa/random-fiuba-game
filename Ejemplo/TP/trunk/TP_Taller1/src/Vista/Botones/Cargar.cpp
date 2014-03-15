/*
 * Cargar.cpp
 *
 *  Created on: 14/09/2013
 *  Last Amended: 24/09/2013
 *      Author: natuchis, rick
 */

#include "Cargar.h"

#include "Vista/Textbox.h"

Cargar::Cargar(const FuentePosicion& unaFuente, Dibujable* unDestino, Textbox* textbox)
	: Boton(unaFuente
	       , Imagen("imagenes/botones/Cargar.png", unDestino)
	       , [textbox] { textbox->grabarCaracter('\n'); }
	       , "imagenes/botones/Cargar.png"
	       , "imagenes/botones/CargarDown.png"
	       , true)
{
}


Cargar::~Cargar() {
}
