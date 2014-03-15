/*
 * Textbox.h
 *
 *  Created on: 24/09/2013
 *      Author: rick
 */

#ifndef TEXTBOX_H_
#define TEXTBOX_H_

#include "Textura.h"
#include "Interfases/Elemento.h"
#include "Texto.h"
#include <functional>

class Textbox : public vista::Elemento {

public:
	Textbox(const FuentePosicion& fuente, Dibujable* destino, std::string textoInicial);
	virtual ~Textbox();
	virtual LayoutInfo getLayoutInfo();
	
	void regenerar();
	virtual void dibujarse(DestinoDibujo* destino);
	virtual bool dirty();
	virtual void grabarCaracter(char caracter);
	virtual vista::ClickInfo recibirClick(Vec2);

	std::string getTexto();
	void setRespuestaEnter(std::function<void(std::string)> fn);
	vista::Color& colorTexto();
	vista::Color& colorFondo();

private:
	Textura apariencia;
	bool dirty_;
	Texto texto;
	std::function<void(std::string)> respuestaEnter;
};

#endif /* TEXTBOX_H_ */

