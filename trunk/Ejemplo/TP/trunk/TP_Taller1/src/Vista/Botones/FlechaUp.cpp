/*
 * FlechaUp.cpp
 *
 *  Created on: 16/09/2013
 *  Last Amended: 16/09/2013
 *      Author: natuchis
 */

#include "FlechaUp.h"

#include "Vista/ToolBar.h"

FlechaUp::FlechaUp(const FuentePosicion& fuente, Dibujable *destino, ToolBar* toolbar)
	: Boton(fuente
	       , Imagen("imagenes/botones/FlechaUp.png", destino)
	       , [toolbar] { toolbar->desplazarHaciaAbajo(Vec2()); }
	       , "imagenes/botones/FlechaUp.png"
	       , "imagenes/botones/FlechaUp.png"
	       , true)
{
}

FlechaUp::~FlechaUp() {
}
