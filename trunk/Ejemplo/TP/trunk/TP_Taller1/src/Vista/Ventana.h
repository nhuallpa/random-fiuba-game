/*
 * Ventana.h
 *
 *  Created on: Sep 5, 2013
 *      Author: lucia
 */

#ifndef VENTANA_H_
#define VENTANA_H_

#include "Utils/Rect.h"
#include "Vista/Interfases/OrigenDestinoDibujo.h"

#include <string>
#include <memory>

class Contenedor;
class Vec2;
class SDL_Renderer;
class SDL_Texture;
class SDL_Window;

class Ventana : public DestinoDibujo
{
public:
	Ventana(int width, int height, std::string title);

	Ventana (const Ventana&) = delete;
	Ventana (Ventana&&) = default;
	Ventana& operator= (const Ventana&) = delete;
	Ventana& operator= (Ventana&&) = default;
	virtual ~Ventana();

	virtual SDL_Renderer* getRenderer ();
	virtual bool valido ();
	virtual SDL_Texture* getTexture ();
	virtual Vec2 tamDibujo () const;

	void resized (Vec2 tam);
	void moved (Vec2 pos);

	void setSuperficie (Rect superficie);
	Rect getSuperficie () const;

	void update ();

	void setRaiz (std::unique_ptr<Contenedor> raiz);
	std::unique_ptr<Contenedor> extraerRaiz ();
	Contenedor* getRaiz () const;

private:
	Rect superficie;
	SDL_Window *window;
	SDL_Renderer *ren;

	std::unique_ptr<Contenedor> raiz;
};

#endif /* VENTANA_H_ */
