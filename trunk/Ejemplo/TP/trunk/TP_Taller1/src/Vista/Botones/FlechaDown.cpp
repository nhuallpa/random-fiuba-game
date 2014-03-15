/*
 * FlechaDown.cpp
 *
 *  Created on: 16/09/2013
 *  Last Amended: 16/09/2013
 *      Author: natuchis
 */

#include "FlechaDown.h"

#include "Vista/ToolBar.h"

FlechaDown::FlechaDown(const FuentePosicion& fuente, Dibujable *destino, ToolBar* toolbar)
	: Boton(fuente
	       , Imagen("imagenes/botones/FlechaDown.png", destino)
	       , [toolbar] { toolbar->desplazarHaciaArriba(Vec2()); }
	       , "imagenes/botones/FlechaDown.png"
	       , "imagenes/botones/FlechaDown.png"
	       , true)
{
}

FlechaDown::~FlechaDown() {
}
