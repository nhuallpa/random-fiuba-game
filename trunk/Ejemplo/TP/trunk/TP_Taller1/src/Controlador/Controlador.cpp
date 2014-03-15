/*
 * Controlador.cpp
 *
 *  Created on: Sep 12, 2013
 *      Author: lucia
 */

#include "Controlador.h"
#include "Vista/ClickInfo.h"
#include "Vista/Ventana.h"
#include "Vista/Contenedor.h"
#include "Vista/Interfases/Elemento.h"
#include "../Sonido/Sonido.h"
#include "Log/Suceso.h"
#include <SDL2/SDL.h>

using namespace std;


Controlador::Controlador(Ventana* window)
	: mouse()
	, teclado()
	, jugador()
	, window(window)
	, modo(Modo::EstadoJuego::edicion)
{
}


Controlador::Controlador(Ventana* window, Modelo::Jugador* jugador)
	: mouse(jugador)
	, teclado()
	, jugador(jugador)
	, window(window)
	, modo(Modo::EstadoJuego::edicion)
{
}


void Controlador::handle(SDL_Event event) {
	using controlador::Mouse;
	// Chequeo los eventos que me interesan
	// SDL_Quit se maneja antes de entrar a este metodo
	switch (event.type) {

	case SDL_WINDOWEVENT:
		if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
			Vec2 tam(event.window.data1, event.window.data2);
			window->resized(tam);
		}
		break;

	case SDL_MOUSEBUTTONDOWN: {
		vista::ClickInfo info = window->getRaiz()->recibirClick(mouse.getPosicionMouse());

		if (event.button.button == SDL_BUTTON_LEFT) {
			switch (modo) {
			case Modo::EstadoJuego::edicion:
				mouse.presionar(Mouse::Boton::izquierdo, window, info);
				break;

			case Modo::EstadoJuego::simulacion:
			case Modo::EstadoJuego::visor:
				mouse.accionar(window, info);
				break;

			default:
				break;
			}
		} else if (event.button.button == SDL_BUTTON_RIGHT) {
			if (this->modo == Modo::EstadoJuego::edicion) {
				mouse.presionar(Mouse::Boton::derecho, window, info);
			}
		}
		if (modo == Modo::EstadoJuego::edicion){
			if (info.tomaFocoTeclado) {
				teclado.enfocar(info.clickeado);
			}
		}
		break;
	}

	case SDL_MOUSEBUTTONUP:
		if (event.button.button == SDL_BUTTON_LEFT) {
			mouse.soltar(Mouse::Boton::izquierdo, window);
		} else if (event.button.button == SDL_BUTTON_RIGHT) {
			mouse.soltar(Mouse::Boton::derecho, window);
		}
		break;

	case SDL_MOUSEMOTION:
		if(this->modo == Modo::EstadoJuego::edicion)
			mouse.realizarMovimiento(Vec2(event.motion.xrel, event.motion.yrel));
		break;

	case SDL_MOUSEWHEEL:
		if(this->modo == Modo::EstadoJuego::edicion) {
			if (event.wheel.y > 0) {
				window->getRaiz()->desplazarHaciaAbajo(mouse.getPosicionMouse());
			} else if (event.wheel.y < 0) {
				window->getRaiz()->desplazarHaciaArriba(mouse.getPosicionMouse());
			}
		}
		break;

	case SDL_KEYDOWN:
		teclado.presionar(event.key.keysym.sym);
		if (teclado.ctrl()) {
			mouse.iniciarEspera(Mouse::Estado::esperaModificar);
		}
		if (teclado.shift()) {
			mouse.iniciarEspera(Mouse::Estado::esperaBorrar);
		}
		if (teclado.esc()) {
			mouse.resetear();
		}
		if (teclado.accion()) {
			if (modo == Modo::EstadoJuego::visor || modo == Modo::EstadoJuego::simulacion) {
				window->getRaiz()->accionarElementos(nullptr, mouse.getPosicionMouse(), Modelo::TipoAccion::levantarFlippers);
			}
		}
		if (teclado.siguiente()) {
			Sonido::Instancia()->siguienteTema();
		}
		if (teclado.anterior()) {
			Sonido::Instancia()->anteriorTema();
		}
		if (teclado.arriba()) {
			Sonido::Instancia()->subirVolumenMusica();
		}
		if (teclado.abajo()) {
			Sonido::Instancia()->bajarVolumenMusica();
		}
		break;

	case SDL_KEYUP:

		teclado.soltar(event.key.keysym.sym);
		if (!teclado.ctrl()) {
			mouse.terminarEspera(Mouse::Estado::esperaModificar);
		}
		if (!teclado.shift()) {
			mouse.terminarEspera(Mouse::Estado::esperaBorrar);
		}
		if (!teclado.accion()) {
			if (modo == Modo::EstadoJuego::visor || modo == Modo::EstadoJuego::simulacion) {
				window->getRaiz()->accionarElementos(nullptr, mouse.getPosicionMouse(), Modelo::TipoAccion::bajarFlippers);
			}
		}

		break;

	case SDL_TEXTINPUT:

		if(this->modo == Modo::EstadoJuego::edicion)
			teclado.input(event.text.text);
		break;
	}
}

void Controlador::cambiarModo(Modo::EstadoJuego modo) {
	this->modo = modo;
}
