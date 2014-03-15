/*
 * Mouse.h
 *
 *  Created on: Sep 13, 2013
 *      Author: lucia
 */

#ifndef MOUSE_H_
#define MOUSE_H_

#include "Utils/Vec2.h"
#include "Vista/Interfases/OrigenDestinoDibujo.h"
#include <cstddef>

union SDL_Event;
class FiguraVista;
class Ventana;

namespace Modelo {
	class Jugador;
}

namespace vista {
	class Elemento;
	class ClickInfo;
}

namespace controlador {

class Mouse {
public:
	Mouse();
	Mouse(Modelo::Jugador*);

	Mouse (const Mouse&) = delete;
	Mouse& operator= (const Mouse&) = delete;
	~Mouse();

	void realizarMovimiento(Vec2 movimiento);
	Vec2 getPosicionMouse() const;

	enum class Estado : size_t;
	void iniciarEspera (Mouse::Estado estado);
	void terminarEspera (Mouse::Estado estado);

	enum class Boton : size_t;
	void presionar (Mouse::Boton boton, Ventana *ventana, vista::ClickInfo info);
	void soltar(Mouse::Boton boton, Ventana *ventana);

	void accionar(Ventana *ventana, vista::ClickInfo info);

	void resetear();

	enum class Boton : size_t {
		izquierdo,
		derecho,
	};

	enum class Estado : size_t {
		inicial, // arrastrando, unionInicial, rotando, esperaBorrar, esperaModificar
		arrastrando, // inicial
		rotando, // inicial
		resizeando, // inicial
		unionInicial, // unionParcial, inicial
		unionParcial, // (uniendo>) inicial, unionInicial
		esperaBorrar, // (borrando>) inicial
		esperaModificar, // inicial, (cambiandoForma>) inicial, resizeando
		clickeandoBoton,
	};

private:
	Modelo::Jugador* jugador;
	Mouse::Estado estado;
	bool esperaModificar;

	vista::Elemento* elemento;
	Vec2 posClickAnterior;

	void iniciarSeleccion(const Ventana *ventana, vista::ClickInfo info);
	void iniciarClickeo(vista::ClickInfo info);
	void iniciarResize(vista::ClickInfo info);
	void iniciarRotacion(vista::ClickInfo info);
	void unir(const Ventana *ventana, vista::ClickInfo info);

	void cambiarModo (Mouse::Estado estado);
	void cambiarModoCursor();
};

} /* namespace controlador */
#endif /* MOUSE_H_ */
