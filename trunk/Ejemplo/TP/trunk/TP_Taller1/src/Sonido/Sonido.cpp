/*
 * Sonido.cpp
 *
 *  Created on: Oct 30, 2013
 *      Author: lucia
 */

#include "Sonido.h"
#include "Log/Suceso.h"

Sonido* Sonido::_instance = nullptr;
bool Sonido::inicializado = false;

Sonido::Sonido ()
	: currMusic(nullptr)
	, efectosCargados()
	, mapaSonidos()
	, mapaSonidosEntidades()
	, fondos()
	, juego()
	, modo(Salida::local)
	, nFondo(0)
	, canalMusica(-1)
	, volumen(VOLUMEN_MUSICA)
	, cantidadFondos(0)
{
	this->inicializarFondos();
	std::string pelotaBasquetGolpeando = "sonidos/BasketBallDrop.wav";
	std::string pelotaBowlingGolpeando = "sonidos/BowlingBall.wav";
	std::string yunqueGolpeando = "sonidos/TROTIMC-Sounds/Sounds_tbv-0000000125-yunque puede ser.wav";
	std::string motor = "sonidos/Sounds_tbv-capaz_motor.wav";
	std::string globoExplotando = "sonidos/BalloonPopping.wav";
	std::string huevoRompiendose = "sonidos/ShortEggCracking.wav";
	std::string flipper = "sonidos/Flipper.wav";
	std::string sogaFuego = "sonidos/Fire.wav";
	std::string tijeraCerrandose = "sonidos/ScissorSnap.wav";

	using Modelo::TipoElemento;

	auto agregar = [&] (TipoElemento lhs, std::string sonido, std::list<TipoElemento> otros) {
		for (auto rhs : otros) {
			mapaSonidos[std::make_pair(lhs, rhs)] = sonido;
			mapaSonidos[std::make_pair(rhs, lhs)] = sonido;
		}
	};

	std::list<TipoElemento> elementosPlataforma = {
		TipoElemento::Plataforma,
		TipoElemento::Balancin,
		TipoElemento::PaletaFlipper,
		TipoElemento::Canio,
		TipoElemento::Codo,
		TipoElemento::Engranaje,
		TipoElemento::Polea,
		TipoElemento::CintaTransportadora};

	agregar(TipoElemento:: PelotaBasquet, pelotaBasquetGolpeando, elementosPlataforma);
	agregar(TipoElemento::PelotaBowling, pelotaBowlingGolpeando, elementosPlataforma);
	agregar(TipoElemento::Yunque, yunqueGolpeando, elementosPlataforma);
	mapaSonidosEntidades[TipoElemento::Motor] = motor;
	mapaSonidosEntidades[TipoElemento::Globo] = globoExplotando;
	mapaSonidosEntidades[TipoElemento::Huevo] = huevoRompiendose;
	mapaSonidosEntidades[TipoElemento::PaletaFlipper] = flipper;
	mapaSonidosEntidades[TipoElemento::Soga] = sogaFuego;
	mapaSonidosEntidades[TipoElemento::Tijera] = tijeraCerrandose;
}

void Sonido::inicializarFondos(){
	Mix_Music* tema1 = Mix_LoadMUS("sonidos/fondos/Pokemon Blue Red - Pallet Town.wav");
	if (tema1) fondos.push_back(tema1);
	Mix_Music* tema2 = Mix_LoadMUS("sonidos/fondos/Pokemon Gold Silver - New Bark Town.wav");
	if (tema2) fondos.push_back(tema2);
	Mix_Music* tema3 = Mix_LoadMUS("sonidos/fondos/Pokemon Ruby Sapphire - Sootopolis City.wav");
	if (tema3) fondos.push_back(tema3);
	Mix_Music* tema4 = Mix_LoadMUS("sonidos/fondos/Pokemon Fire Red and Leaf Green - Pokemon Center.wav");
	if (tema4) fondos.push_back(tema4);
	Mix_Music* tema5 = Mix_LoadMUS("sonidos/fondos/Pokemon Heart Gold Soul Silver - Final Battle Vs Red.wav");
	if (tema5) fondos.push_back(tema5);
	Mix_Music* tema6 = Mix_LoadMUS("sonidos/fondos/Ocarina Of Time - Kokiri Forest.wav");
	if (tema6) fondos.push_back(tema6);
	nFondo = 0;
	cantidadFondos = 6;
}

void Sonido::subirVolumenMusica() {
	if(volumen <= VOLUMEN_MAXIMO) {
		volumen+=5;
		Mix_VolumeMusic(volumen);
	}

}

void Sonido::bajarVolumenMusica() {
	float nuevoVolumen = volumen - 5;
	if(nuevoVolumen >= 0) {
		volumen = nuevoVolumen;
		Mix_VolumeMusic(volumen);
	}

}

Mix_Music* Sonido::getTrack(int n) {
	int cont = 0;
	std::list<Mix_Music*>::iterator it;
	for(it = fondos.begin(); it != fondos.end(); it++) {
		if (cont == n) {
			return *it;
		}
		cont++;
	}
	return *fondos.begin();
}

void Sonido::siguienteTema() {
	// Aca arranca
	if (canalMusica == -1) {
		currMusic = getTrack(nFondo);
		canalMusica = playMusic(currMusic);
		nFondo++;
		return;
	} else {
		if (nFondo != cantidadFondos) {
			Mix_HaltChannel(canalMusica);
			currMusic = getTrack(nFondo);
			canalMusica = playMusic(currMusic);
			++nFondo;
		}
	}
}

void Sonido::anteriorTema() {
	if ((canalMusica != -1) && (nFondo != 0)) {
		Mix_HaltChannel(canalMusica);
		currMusic = getTrack(nFondo);
		canalMusica = playMusic(currMusic);
		nFondo--;
	}
}

float Sonido::playMusic(Mix_Music* mus) {
	float canal = Mix_PlayMusic( mus, -1 );
	Mix_VolumeMusic(volumen);
	return canal;

}

void Sonido::playMusic(std::string path) {
	this->currMusic = Mix_LoadMUS( path.c_str() );
	Mix_PlayMusic( currMusic, -1 );
	Mix_VolumeMusic(VOLUMEN_MUSICA);
}

void Sonido::playSound(std::string path) {
	this->playSound(path, 0);
}


void Sonido::actualizar() {
	if (modo == Salida::red) {
		juego->musica.clear();
	}

}

void Sonido::playSound(std::string path, int loop) {
	switch(modo) {
		case Salida::local: {
			playSoundInterno(path, loop);
			break;
		}
		case Salida::red: {
			juego->musica.clear();
			// 1 puede ser un flag de frenar efectos.
			juego->musica.push_back(make_pair(0, path));
			break;
		}
		default:
			break;
	}
}

void Sonido::playSoundInterno(std::string path, int loop) {
	std::map<std::string, Mix_Chunk*>::iterator it;
	it = efectosCargados.find(path);
	if (it != efectosCargados.end()) {
		// Ya lo tiene y le doy play
		Mix_Chunk* currEfecto = it->second;
		Mix_PlayChannel( -1, currEfecto, loop);
	} else {
		Mix_Chunk* currEfecto = Mix_LoadWAV( path.c_str() );
		if (currEfecto) {
			efectosCargados.insert(make_pair(path,currEfecto));
		}
		Mix_VolumeChunk(currEfecto, VOLUMEN_EFECTOS);
		Mix_PlayChannel( -1, currEfecto, loop);
	}
}

Sonido* Sonido::Instancia(){
	if (!inicializado) {
		inicializado = true;
		// Inicializo SDL_mixer (numeros sacados de lazyfoo)
		// Solo wav
		if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 ) {
			Log::Suceso(Log::ERROR, Mix_GetError());
			return nullptr;
		}
		_instance = new Sonido();
	}
	return _instance;
}


void Sonido::playSound(Modelo::EntidadWrapper e1, Modelo::EntidadWrapper e2) {

	std::map<std::pair<Modelo::TipoElemento,Modelo::TipoElemento> ,std::string>::iterator it;
	it = mapaSonidos.find(std::make_pair(e1.clase(), e2.clase()));

	if (it != mapaSonidos.end()) {
		std::string path = it->second;
		this->playSound(path);
	}
}

void Sonido::playSound(Modelo::EntidadWrapper e1) {
	std::map<Modelo::TipoElemento, std::string>::iterator it;
	it = mapaSonidosEntidades.find(e1.clase());
	if (it != mapaSonidosEntidades.end()) {
		std::string path = it->second;
		this->playSound(path);
	}
}

void Sonido::stopEfectos() {
	std::map<std::string, Mix_Chunk*>::iterator it;
	int canalEfectos;
	for(int i = 1; i < 2; i++) {
		if (canalMusica != i)
			canalEfectos = i;
	}
	Mix_HaltChannel(canalEfectos);
}

void Sonido::limpiar() {
	std::map<std::string, Mix_Chunk*>::iterator it;
	for (it = efectosCargados.begin(); it != efectosCargados.end(); ++it) {
		Mix_Chunk* currEfecto = it->second;
		Mix_FreeChunk( currEfecto );
	}
	std::list<Mix_Music*>::iterator itMus;
	for(itMus = fondos.begin(); itMus != fondos.end(); itMus++){
		Mix_FreeMusic( *itMus );
	}
	Mix_CloseAudio();
}

void Sonido::setSalida(Salida modo) {
	this->modo = modo;
}

void Sonido::setJuego(Modelo::Juego* juego) {
	this->juego = juego;
}
