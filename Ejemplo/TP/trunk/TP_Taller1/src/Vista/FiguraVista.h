/*
 * FiguraVista.h
 *
 *  Created on: Sep 5, 2013
 *      Author: lucia
 */

#ifndef FIGURAVista_H_
#define FIGURAVista_H_

#include "Interfases/Elemento.h"
#include "Modelo/TipoElemento.h"
#include "Vista/Imagen.h"
#include <string>
#include <map>

class FuentePosicion;
class Vec2;
class DestinoDibujo;
class LayoutInfo;

class FiguraVista : public vista::Elemento {
public:
	FiguraVista();
	FiguraVista (Modelo::TipoElemento tipo, const FuentePosicion& fuente, Dibujable *destino);

	FiguraVista (const FiguraVista&) = default;
	FiguraVista (FiguraVista&&) = default;
	FiguraVista& operator= (const FiguraVista&) = default;
	FiguraVista& operator= (FiguraVista&&) = default;
	virtual ~FiguraVista();

	virtual void dibujarse(DestinoDibujo* window);
	virtual void setSuperfice(const Rect& val);

	virtual LayoutInfo getLayoutInfo();

	virtual bool contiene(Vec2 punto);
	virtual vista::ClickInfo recibirClick(Vec2 pos);
	virtual void mover(Vec2 incremento);
	virtual void rotar(Vec2 respectoA);
	virtual bool aEliminar (Vec2 posicion);
	virtual void resizear(Vec2 respectoA);
	virtual void cambiarForma();
	virtual vista::Elemento* clonar() const;

	Modelo::TipoElemento getClase();

private:
	std::string pathImagen;
	Imagen imagen;
	Modelo::TipoElemento clase;

	double getAnguloRotacion(Vec2 respectoA);

	// para cambios de forma
	void ciclarEntreRadios();
	void ciclarEntreAngulos();
	void ciclarEntreGiros();
	void ciclarEntreGirosTijera();
	void cambiarImagen(std::string path);

	void verificarImagen();

	// para animacion de la cinta
	unsigned cantEngranajes() const;
	unsigned estadoRotacion() const;

	unsigned estadoAnimacion;
	unsigned contadorAnimacion;
};

#endif /* FIGURAVista_H_ */
