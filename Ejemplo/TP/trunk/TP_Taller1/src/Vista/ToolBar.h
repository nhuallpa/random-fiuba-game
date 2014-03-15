/*
 * ToolBar.h
 *
 *  Created on: 15/09/2013
 *      Author: stephanie
 */

#ifndef TOOLBAR_H_
#define TOOLBAR_H_

#include "Contenedor.h"

class Canvas;
namespace Modelo {
	class Juego;
}

class ToolBar:public Contenedor{
public:
	ToolBar(const FuentePosicion& fuente, Dibujable* destino, Canvas *canvas, Modelo::Juego *juego);

	ToolBar (const ToolBar&) = delete;
	ToolBar& operator= (const ToolBar&) = delete;
	virtual ~ToolBar();

	void subirToolBar();
	void bajarToolBar();

	virtual vista::ClickInfo recibirClick(Vec2);
	virtual void desplazarHaciaArriba(Vec2 posicion);
	virtual void desplazarHaciaAbajo(Vec2 posicion);
	virtual LayoutInfo getLayoutInfo();
	virtual bool dirty();

	int getPosicionEnToolbar();

private:
	static const int espacioEntreFiguras;
	static const int desplazamientoInicial;
	static const float desplazamientoFraccional;
	static const float tamFiguraEnUL;

	int posicionEnToolbar;
	Canvas *canvas;
	Modelo::Juego *juego;

	void actualizarPosicionEnToolbar(Rect fig);
	virtual void regenerar();
	void actualizarSuperficiesFiguras(vista::Elemento* figura);
	void actualizarCantidad (vista::Elemento* figura);
};

#endif /* TOOLBAR_H_ */
