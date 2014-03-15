/*
 * Sonido.h
 *
 *  Created on: Oct 30, 2013
 *      Author: lucia
 */

#ifndef SONIDO_H_
#define SONIDO_H_

#include "Modelo/EntidadWrapper.h"
#include "Modo/ModoUsuario.h"
#include "Modelo/Juego.h"
#include <SDL2/SDL_mixer.h>
#include <string>
#include <map>
#include <set>

#define VOLUMEN_MUSICA 10
#define VOLUMEN_EFECTOS 15
#define VOLUMEN_MAXIMO 30

enum class Salida : size_t {
	red,
	local,
};

class Sonido {

public:
	static Sonido* Instancia();
	void playMusic(std::string path);

	void siguienteTema();
	void anteriorTema();
	void subirVolumenMusica();
	void bajarVolumenMusica();


	//Para choques
	void playSound(Modelo::EntidadWrapper e1, Modelo::EntidadWrapper e2);
	void playSound(Modelo::EntidadWrapper e1);
	void playSound(std::string path);

	void setSalida(Salida modo);
	void setJuego(Modelo::Juego* juego);

	void stopEfectos();

	Mix_Music* getTrack(int n);

	//Se llama al salir del programa
	void limpiar();

	void actualizar();

protected:
	Sonido ();
	Sonido (Sonido const&) = delete;
	Sonido& operator=(Sonido const&) = delete;

private:
	void playSound(std::string path, int loop);
	float playMusic(Mix_Music* mus);
	void inicializarFondos();
	static Sonido* _instance;
	static bool inicializado;
	Mix_Music *currMusic;
	std::map<std::string, Mix_Chunk*> efectosCargados;
	std::map<std::pair<Modelo::TipoElemento,Modelo::TipoElemento> ,std::string> mapaSonidos;
	std::map<Modelo::TipoElemento, std::string> mapaSonidosEntidades;
	std::list<Mix_Music*> fondos;
	Modelo::Juego* juego;
	Salida modo;
	int nFondo;
	int canalMusica;
	float volumen;
	int cantidadFondos;
	void playSoundInterno(std::string path, int loop);

};


#endif /* SONIDO_H_ */
