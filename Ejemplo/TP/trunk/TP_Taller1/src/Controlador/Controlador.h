/*
 * Controlador.h
 *
 *  Created on: Sep 12, 2013
 *      Author: lucia
 */

#ifndef CONTROLADOR_H_
#define CONTROLADOR_H_

#include "Controlador/Mouse.h"
#include "Controlador/Teclado.h"
#include "Modo/ModoUsuario.h"

class Ventana;
class Contenedor;

class Controlador {
public:
	Controlador(Ventana*);
	Controlador(Ventana*, Modelo::Jugador*);

	Controlador (const Controlador&) = delete;
	//Controlador (Controlador&&) = ?;
	Controlador& operator= (const Controlador&) = delete;
	//Controlador& operator= (Controlador&&) = ?;
	~Controlador() = default;

	void handle(SDL_Event event);
	Contenedor* getContenedorClickeado();

	void cambiarModo(Modo::EstadoJuego modo);
private:
	controlador::Mouse mouse;
	controlador::Teclado teclado;
	Modelo::Jugador* jugador;
	Ventana* window;

	Modo::EstadoJuego modo;
};

#endif /* CONTROLADOR_H_ */
