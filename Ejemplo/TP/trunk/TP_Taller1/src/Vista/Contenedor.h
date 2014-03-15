/*
 * Contenedor.h
 *
 *  Created on: Sep 5, 2013
 *      Author: lucia
 */

#ifndef CONTENEDOR_H_
#define CONTENEDOR_H_

#include "Textura.h"
#include "Interfases/Elemento.h"
#include "Modelo/EntidadWrapper.h"
#include <list>
#include <map>
#include <string>
#include <memory>

class FuentePosicion;
class DestinoDibujo;
class OrigenDibujo;
class Vec2;
class Rect;
class LayoutInfo;

namespace vista {
	class ClickInfo;
}

class Contenedor : public vista::Elemento
{
public:
	Contenedor(const FuentePosicion& fuente, Dibujable* destino);
	virtual ~Contenedor();

	void addElemento(vista::Elemento* elemento, vista::PrioridadDibujo prioridad = vista::PrioridadDibujo::normal);
	void quitarElemento(vista::Elemento* elemento);
	void vaciar();

	void setBackground(std::string filename, Dibujable* destino);
	void setBackground(vista::Color color, Dibujable* destino);
	void setBackground(std::unique_ptr<OrigenDibujo> fondo);
	void setPermitirEliminaciones (bool permitido);

	virtual void dibujarse(DestinoDibujo* ventana);
	virtual bool dirty();

	virtual LayoutInfo getLayoutInfo();

	virtual vista::ClickInfo recibirClick(Vec2);
	virtual void desplazarHaciaArriba(Vec2 posicion);
	virtual void desplazarHaciaAbajo(Vec2 posicion);
	virtual bool aEliminar (Vec2 posicion);
	virtual bool recibirFigura (const FiguraVista *elemento, Vec2 pos,
			vista::PrioridadDibujo prioridad = vista::PrioridadDibujo::normal);
	virtual bool recibirElementoPuente(FiguraVista *elemento, Vec2 extremoA,
			Vec2 extremoB, vista::PrioridadDibujo prioridad = vista::PrioridadDibujo::normal);
	virtual std::pair<bool,Rect> superficieAbsoluta (Elemento *elemento);
	virtual void resized (Vec2 tam);
	virtual bool accionarElementos(FiguraVista* figura, Vec2 pos, Modelo::TipoAccion accion);

protected:
	std::unique_ptr<OrigenDibujo> fondo;
	Textura apariencia;
	bool permitirEliminaciones;
	bool dirty_;

	virtual void regenerar();
	vista::Elemento* buscar_base (Vec2 posicion);
	std::list<vista::Elemento*> listarElementos();

private:
	std::map<vista::PrioridadDibujo, std::list<vista::Elemento*>> elementos;
};

#endif /* CONTENEDOR_H_ */
