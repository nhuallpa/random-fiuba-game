/*
 * Boton.h
 *
 *  Created on: 14/09/2013
 *  Last Amended: 14/09/2013
 *      Author: natuchis
 */

#ifndef BOTON_H_
#define BOTON_H_

#include "Vista/Imagen.h"
#include "Vista/Textura.h"
#include "Vista/Interfases/Elemento.h"
#include <string>

class Vec2;
class Rect;
class FuentePosicion;

class Boton : public vista::Elemento {
public:
	Boton(const FuentePosicion& fuente, Imagen imagen, std::function<void()> reaccion,
			std::string imagenUp, std::string imagenDown, bool cambiante);
	Boton(const FuentePosicion& fuente, Textura imagen, std::function<void()> reaccion);

	Boton (const Boton&) = default;
	Boton (Boton&&) = default;
	Boton& operator= (const Boton&) = default;
	Boton& operator= (Boton&&) = default;
	virtual ~Boton();

	virtual void dibujarse(DestinoDibujo* window);
	virtual vista::ClickInfo recibirClick (Vec2 pos);
	virtual bool dirty();

	LayoutInfo getLayoutInfo();

	void cambiarImagen();
	void cambiarImagen(std::string pathImagen);

private:
	std::unique_ptr<OrigenDibujo> imagen;
	std::function<void()> reaccion;

protected:
	bool up;
	std::string imagenUp;
	std::string imagenDown;
	bool cambiante;
};

#endif /* BOTON_H_ */
