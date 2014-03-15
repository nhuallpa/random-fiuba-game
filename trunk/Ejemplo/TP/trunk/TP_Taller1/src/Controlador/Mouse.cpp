/*
 * Mouse.cpp
 *
 *  Created on: Sep 13, 2013
 *      Author: lucia
 */

#include "Mouse.h"

#include "Controlador/Cursor.h"
#include "Utils/make_unique.h"
#include "Vista/ClickInfo.h"
#include "Vista/Contenedor.h"
#include "Vista/FiguraVista.h"
#include "Vista/Ventana.h"
#include "Vista/Interfases/Elemento.h"
#include "Vista/FuentesPosicion/FuenteMouse.h"
#include "Vista/FuentesPosicion/FuenteModelo.h"
#include <SDL2/SDL_mouse.h>
#include <map>

namespace controlador {

Mouse::Mouse()
	: jugador(nullptr)
	, estado(Estado::inicial)
	, esperaModificar(false)
	, elemento(NULL)
	, posClickAnterior()
{
	cambiarModo(estado);
}

Mouse::Mouse(Modelo::Jugador* jugador)
	: jugador(jugador)
	, estado(Estado::inicial)
	, esperaModificar(false)
	, elemento(NULL)
	, posClickAnterior()
{
	cambiarModo(estado);
}

Mouse::~Mouse() {
	resetear();
}

void Mouse::iniciarEspera (Mouse::Estado espera) {
	if (estado == Estado::inicial) {
		if (espera == Estado::esperaBorrar) {
			cambiarModo(espera);
		} else if (espera == Estado::esperaModificar) {
			esperaModificar = true;
			cambiarModo(espera);
		}
	}
}

void Mouse::terminarEspera (Mouse::Estado espera) {
	if (estado == espera) {
		if (espera == Estado::esperaBorrar) {
			cambiarModo(Estado::inicial);
		} else if (espera == Estado::esperaModificar) {
			esperaModificar = false;
			cambiarModo(Estado::inicial);
		}
	}
}

void Mouse::iniciarSeleccion(const Ventana *ventana, vista::ClickInfo info)
{
	if (estado != Estado::inicial || info.clickeado == NULL) {
		return;
	}
	auto elementoBuscado = info.clickeado->clonar();
	if (elementoBuscado == NULL) return;

	auto figura = dynamic_cast<FiguraVista*>(elementoBuscado);
	if (figura == nullptr) {
		// Si no voy a poder soltarlo, no lo tomo.
		return;
	}

	FuenteMouse *nFuente = new FuenteMouse(ventana, this, elementoBuscado->getFuente());
	elementoBuscado->setFuente(nFuente);

	cambiarModo(Estado::arrastrando);
	elemento = elementoBuscado;
	if (jugador != nullptr) {
		jugador->elementoMouse = figura->getClase();
		jugador->fuenteMouse = nFuente;
	}

	ventana->getRaiz()->aEliminar(getPosicionMouse());
	ventana->getRaiz()->addElemento(elemento, vista::PrioridadDibujo::arrastrando);
}

void Mouse::iniciarClickeo(vista::ClickInfo info) {
	if (estado != Estado::inicial || info.clickeado == NULL) {
		return;
	}

	auto elementoBuscado = info.clickeado->clonar();
	if (elementoBuscado == NULL) return;

	cambiarModo(Estado::unionInicial);
	elemento = elementoBuscado;
}

void Mouse::iniciarResize(vista::ClickInfo info) {
	if (estado != Estado::esperaModificar || info.clickeado == NULL) {
		return;
	}

	cambiarModo(Estado::resizeando);
	elemento = info.clickeado;
}

void Mouse::iniciarRotacion(vista::ClickInfo info) {
	if (estado != Estado::inicial || info.clickeado == NULL) {
		return;
	}

	cambiarModo(Estado::rotando);
	elemento = info.clickeado;
}

// TODO ver como acceder a los chequeos de las entidades e indicar union.
// Necesito ventana??
void Mouse::unir(const Ventana *ventana, vista::ClickInfo info) {
	// figura corresponde a la soga o la correa, cuando inicio el clickeo
	// info.clickeado corresponde al elemento clickeado para unir
	if (estado != Estado::unionInicial && estado != Estado::unionParcial) {
		return;
	}

	FiguraVista* figura = dynamic_cast<FiguraVista*>(elemento);
	if (figura == nullptr) {
		return;
	}
	Modelo::TipoElemento clase = figura->getClase();

	FiguraVista *figuraActual = dynamic_cast<FiguraVista*>(info.clickeado);
	if (figuraActual == nullptr) {
		return;
	}
	Modelo::TipoElemento claseActual = figuraActual->getClase();

	FuenteModelo *fuenteActual = dynamic_cast<FuenteModelo*>(figuraActual->getFuente());
	if (fuenteActual == nullptr) {
		return;
	}
	Modelo::EntidadWrapper entidadActual = fuenteActual->getEntidad();

	bool avanzarEstado = false;
	if (entidadActual.elemPuenteAtado().size() < entidadActual.lugarDondeSePuedeUnir().size()) {
		if (clase == Modelo::TipoElemento::Correa && Modelo::esCorreable(claseActual)) {
			avanzarEstado = true;
		} else if (clase == Modelo::TipoElemento::Soga && Modelo::esSogeable(claseActual)) {
			avanzarEstado = true;
		}
	}

	if (avanzarEstado) {
		if (estado == Estado::unionInicial) {
			posClickAnterior = getPosicionMouse();
			cambiarModo(Estado::unionParcial);
		} else if (estado == Estado::unionParcial) {
			ventana->getRaiz()->recibirElementoPuente(figura, posClickAnterior, getPosicionMouse());
			resetear();
		}
	}
}

void Mouse::realizarMovimiento(Vec2 movimiento){
	switch (estado) {
	case Estado::rotando:
		elemento->rotar(this->getPosicionMouse());
		break;

	case Estado::resizeando:
		elemento->resizear(movimiento);
		break;

	default:
		break;
	}
}

Vec2 Mouse::getPosicionMouse() const{
	int x, y;
	SDL_GetMouseState(&x, &y);
	if (jugador != nullptr)
		jugador->posicionMouse = Vec2(x, y);
	return Vec2(x, y);
}

void Mouse::presionar (Mouse::Boton boton, Ventana *ventana, vista::ClickInfo info) {
	switch (estado) {
	case Estado::inicial:
		if (boton == Boton::izquierdo) {
			if (info.puedeArrastrar) {
				iniciarSeleccion(ventana, info);
			} else if (info.iniciaClickeo) {
				iniciarClickeo(info);
			} else if (info.esBotonCambiante){
				info.clickeado->cambiarImagen();
				cambiarModo(Estado::clickeandoBoton);
				elemento = info.clickeado;
			}
		} else if (boton == Boton::derecho) {
			if (info.puedeRotar) {
				iniciarRotacion(info);
			}
		}
		break;

	case Estado::unionInicial:
	case Estado::unionParcial:
		if (boton == Boton::izquierdo) {
			unir(ventana, info);
		}
		break;

	case Estado::esperaBorrar:
		ventana->getRaiz()->aEliminar(getPosicionMouse());
		break;

	case Estado::esperaModificar:
		if (boton == Boton::derecho) {
			if (info.puedeResizear) {
				iniciarResize(info);
			} else if (info.clickeado != nullptr) {
				info.clickeado->cambiarForma();
			}
		}
		break;

	default:
		break;
	}
}

void Mouse::soltar(Mouse::Boton boton, Ventana *ventana) {
	switch (estado) {
	case Estado::arrastrando:
		if (boton == Boton::izquierdo) {
			ventana->getRaiz()->quitarElemento(elemento);
			// Ya se verifico que da figura != nullptr en presionar
			FiguraVista* figura = dynamic_cast<FiguraVista*>(elemento);
			ventana->getRaiz()->recibirFigura(figura, getPosicionMouse());
			cambiarModo(Estado::inicial);
		}
		break;

	case Estado::resizeando:
		if (boton == Boton::derecho) {
			cambiarModo(esperaModificar ? Estado::esperaModificar : Estado::inicial);
		}
		break;

	case Estado::rotando:
		if (boton == Boton::derecho) {
			cambiarModo(Estado::inicial);
		}
		break;
	case Estado::clickeandoBoton:
		if (elemento)
			elemento->cambiarImagen();
		cambiarModo(Estado::inicial);
		break;

	default:
		break;
	}
}

void Mouse::cambiarModo (Mouse::Estado nEstado)
{
	if (jugador != nullptr) {
		jugador->estadoMouse = nEstado;
	}
	if (estado == Estado::arrastrando && nEstado != Estado::arrastrando) {
		delete elemento;
	}
	if (nEstado != Estado::unionInicial && nEstado != Estado::unionParcial) {
		elemento = nullptr;
	}
	estado = nEstado;
	cambiarModoCursor();
}

void Mouse::cambiarModoCursor() {
	static Cursor cursorDefault("imagenes/punteros/single-click.png", 6, 2);
	static Cursor cursorRotar("imagenes/punteros/rotate.png", 12, 12);
	static Cursor cursorDosClicks("imagenes/punteros/wizard.png", 9, 5);
	static Cursor cursorResize("imagenes/punteros/arrow_resize.png", 1, 7);
	static Cursor cursorDelete("imagenes/punteros/delete.png", 6, 2);

	switch (estado) {
	case Estado::esperaModificar:
	case Estado::resizeando:
		cursorResize.activar();
		break;

	case Estado::rotando:
		cursorRotar.activar();
		break;

	case Estado::unionInicial:
	case Estado::unionParcial:
		cursorDosClicks.activar();
		break;

	case Estado::esperaBorrar:
		cursorDelete.activar();
		break;

	default:
		cursorDefault.activar();
		break;
	}
}

void Mouse::resetear() {
	cambiarModo(Estado::inicial);
}

void Mouse::accionar(Ventana *ventana, vista::ClickInfo info) {
	if (info.esCanvas) {
		FiguraVista* figura = dynamic_cast<FiguraVista*>(info.clickeado);
		ventana->getRaiz()->accionarElementos(figura, getPosicionMouse(), Modelo::TipoAccion::clickearFigura);
	}
}

} /* namespace controlador */
