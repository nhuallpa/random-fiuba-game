/*
 * Guardar.cpp
 *
 *  Created on: 14/09/2013
 *  Last Amended: 15/09/2013
 *      Author: natuchis
 */

#include "Guardar.h"

#include "Modelo/Juego.h"
#include "Serializacion/Juego.h"
#include "Serializacion/YAML/archivo.h"

Guardar::Guardar(const FuentePosicion& fuente, Dibujable *destino, Modelo::Juego* juego,
                 std::string pathArch)
	: Boton(fuente
		, Imagen("imagenes/botones/Guardar.png", destino)
		, [=] () { YAML_escribirArchivo(pathArch, *juego); }
		, "imagenes/botones/Guardar.png"
		, "imagenes/botones/GuardarDown.png"
		, true)
{
}

Guardar::~Guardar() {
}
