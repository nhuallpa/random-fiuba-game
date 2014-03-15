/*
 * Texto.h
 *
 *  Created on: 02/10/2013
 *  Last Amended: 02/10/2013
 *      Author: natuchis
 */

#ifndef TEXTO_H_
#define TEXTO_H_

#include "Vista/Interfases/OrigenDestinoDibujo.h"
#include <memory>
#include <string>

namespace vista {
	class Color;
}
class FuentePosicion;
class Dibujable;
class Rect;


class Texto: public OrigenDibujo {
public:
	Texto();
	Texto(Dibujable* destino, std::string textoInicial);

	Texto (const Texto&) = delete;
	Texto (Texto&&) = default;
	Texto& operator= (const Texto&) = delete;
	Texto& operator= (Texto&&) = default;
	virtual ~Texto();

	virtual bool valido ();
	virtual SDL_Renderer* getRenderer ();
	virtual SDL_Texture* getTexture ();

	void dibujarse(DestinoDibujo* destino, Rect superficie, Vec2 padre);
	Vec2 tamDibujo () const;

	std::string getTexto();
	void setTexto(std::string unTexto);
	vista::Color& colorFondo();
	vista::Color& colorTexto();

	void limpiarTexto();

private:
	struct Impl;
	std::unique_ptr<Impl> impl;

	void regenerar() const;
	void setApariencia (Dibujable& destino) const;

};

#endif /* TEXTO_H_ */
