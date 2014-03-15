/*
 * Elemento.h
 *
 *  Created on: Sep 13, 2013
 *      Author: lucia
 */

#ifndef ELEMENTO_H_
#define ELEMENTO_H_

#include "Utils/Vec2.h"
#include "Modelo/Jugador.h"
#include "Modelo/EntidadWrapper.h"
#include <memory>
#include <iostream>

class Rect;
class DestinoDibujo;
class FuentePosicion;
class LayoutInfo;
class Ventana;
class Contenedor;
class FiguraVista;

namespace vista {

class ClickInfo;
enum class PrioridadDibujo : int {
	// menor es mas visible
	barraAbajo = -3,
	arrastrando = -2,
	canio = -1,
	normal = 0,
	soga = 1
};

//Clase abstracta que modela cualquier elemento que pueda formar parte de la pantalla
class Elemento {
public:
	Elemento ();
	Elemento (const FuentePosicion& fuente);

	Elemento (const Elemento& base);
	Elemento (Elemento&&) = default;
	Elemento& operator= (const Elemento&);
	Elemento& operator= (Elemento&&) = default;
	virtual ~Elemento();

	// dibujo
	virtual void dibujarse(DestinoDibujo* destino) = 0;
	virtual Rect getSuperficie() const; //relativa a su padre
	virtual void setSuperfice(const Rect&) {};
	virtual FuentePosicion* getFuente () const;
	virtual void setFuente(FuentePosicion* fuente);
	virtual bool dirty();

	// informacion de tamaño
	virtual LayoutInfo getLayoutInfo() = 0;

	// control de visibilidad
	virtual void ocultar();
	virtual void mostrar();
	virtual bool visibilidad();

	// respuesta a eventos
	virtual bool contiene(Vec2 punto);
	virtual ClickInfo recibirClick(Vec2 pos);
	virtual void mover(Vec2) {};
	virtual void desplazarHaciaArriba(Vec2) {};
	virtual void desplazarHaciaAbajo(Vec2) {};
	virtual void rotar(Vec2) {};
	virtual bool aEliminar (Vec2 posicion);
	virtual bool recibirFigura (const FiguraVista *elemento, Vec2 pos,
			PrioridadDibujo prioridad);
	virtual bool recibirElementoPuente(FiguraVista *elemento, Vec2 extremoA,
			Vec2 extremoB, vista::PrioridadDibujo prioridad);
	virtual void grabarCaracter(char) {};
	virtual void resizear(Vec2) {}; // transformada activa, de uso general
	virtual void resized(Vec2) {}; // transformada pasiva, para vista
	virtual std::pair<bool,Rect> superficieAbsoluta (Elemento *elemento);

	virtual bool accionarElementos(FiguraVista* fig, Vec2 pos, Modelo::TipoAccion accion);

	virtual void cambiarForma() {};

	virtual Elemento* clonar() const;

	virtual void cambiarImagen() {};

protected:
	bool visible;
	std::unique_ptr<FuentePosicion> fuente;
};

} /* namespace interfases */
#endif /* ELEMENTO_H_ */
