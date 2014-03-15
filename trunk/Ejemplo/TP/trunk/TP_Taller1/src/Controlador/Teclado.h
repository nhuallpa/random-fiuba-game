/*
 * Teclado.h
 *
 *  Created on: Sep 13, 2013
 *      Author: lucia
 */

#ifndef TECLADO_H_
#define TECLADO_H_

#include <SDL2/SDL_keycode.h>
#include <set>

namespace vista {
	class Elemento;
}

namespace controlador {

class Teclado {

public:
	Teclado();

	Teclado (const Teclado&) = default;
	Teclado (Teclado&&) = default;
	Teclado& operator= (const Teclado&) = default;
	Teclado& operator= (Teclado&&) = default;
	~Teclado() = default;

	void presionar (SDL_Keycode tecla);
	void soltar (SDL_Keycode tecla);
	void input (const char *texto);

	void enfocar (vista::Elemento *elemento);
	void desenfocar ();

	bool presionada(SDL_Keycode tecla);
	bool shift();
	bool ctrl();
	bool r();
	bool esc();
	//Devuelve true si se presiona la tecla de accion (a)
	bool accion();
	bool siguiente();
	bool anterior();
	bool arriba();
	bool abajo();

private:
	std::set<SDL_Keycode> presionadas;
	vista::Elemento* elemento;
};


} /* namespace controlador */

#endif /* TECLADO_H_ */

