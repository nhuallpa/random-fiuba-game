#include "mainJuego.h"

#include "Controlador/Controlador.h"
#include "Modelo/Juego.h"
#include "Modo/Aviso.h"
#include "Modo/ModoEdicion.h"
#include "Red/Cliente.h"
#include "Serializacion/Juego.h"
#include "Serializacion/Interno/Mapa.h"
#include "Serializacion/YAML/archivo.h"
#include "Sonido/Sonido.h"
#include "Utils/make_unique.h"
#include "Vista/Ventana.h"

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>


//
//vista::Color(245,180,100);
//
void ciclarJuego (Cliente *cliente, Modelo::Juego *juego, Serializacion::Objeto *ultimoJuegoLeido)
{
	if (!cliente->vivo()) {
		throw Log::Suceso(Log::FATAL, "Cliente muerto.");
	}
	Serializacion::Objeto delta = ultimoJuegoLeido->diferencia(*juego);
	if (delta.getMapa().atributos.size() != 0) {
		cliente->push(std::move(delta));
	}

	*ultimoJuegoLeido = cliente->getCanonico();
	juego->asignacionProfunda(*ultimoJuegoLeido);
	juego->miJugador = cliente->getTipoJugador();
}

void subMainJuego (Cliente *cliente, const char *archivoSalida)
{
	Modelo::Juego juego;
	Serializacion::Objeto ultimoJuegoLeido;
	if (cliente == nullptr) {
		ultimoJuegoLeido = YAML_leerArchivo(archivoSalida);
		juego = ultimoJuegoLeido;
	} else {
		ultimoJuegoLeido = cliente->getCanonico();
		juego = ultimoJuegoLeido;
		juego.miJugador = cliente->getTipoJugador();
		juego.jugadores[juego.miJugador].modoJuegoActual = Modo::EstadoJuego::edicion;
	}

	// Se crea la ventana principal.
	std::string titulo = "The Incredible Machine";
	if (cliente != nullptr) {
		titulo += " - " + Modelo::tipoJugadorToString(juego.miJugador);
	}
	Ventana window(800, 700, titulo);
	Controlador* controlador;
	if (cliente != nullptr) {
		controlador = new Controlador(&window, &juego.jugadores[juego.miJugador]);
	} else {
		controlador = new Controlador(&window);
	}
	std::unique_ptr<Modo::ModoJuego> modo;
	modo = make_unique<Modo::ModoEdicion>(&window, &juego, std::string(archivoSalida));
	if (cliente != nullptr) {
		modo = make_unique<Modo::Aviso>(std::move(modo), Modo::TipoAviso::Mision, juego.objetivo.descripcion);
	}

	auto sonido = Sonido::Instancia();
	int n = rand() % 5;

	if (sonido != nullptr) {
		if (n == 0) {
			sonido->playMusic("sonidos/fondos/Pokemon Blue Red - Pallet Town.wav");
		}
		else if (n == 1) {
			sonido->playMusic("sonidos/fondos/Pokemon Gold Silver - New Bark Town.wav");
		}
		else if (n == 2) {
			sonido->playMusic("sonidos/fondos/Pokemon Ruby Sapphire - Sootopolis City.wav");
		}
		else if (n == 3) {
			sonido->playMusic("sonidos/fondos/Pokemon Fire Red and Leaf Green - Pokemon Center.wav");
		}
		else if (n == 4) {	// Musica de boss final (mmmm bueno... en este caso un nivel muy dificil  :P )
			sonido->playMusic("sonidos/fondos/Pokemon Heart Gold Soul Silver - Final Battle Vs Red.wav");
		}
	}

	// Ciclo infinito principal
	uint32_t ultimo = SDL_GetTicks();
	while (true) {
		SDL_Event event;
		while (SDL_PollEvent(&event) != 0) {
			if (event.type == SDL_QUIT) {
				delete controlador;
				return;
			} else {
				controlador->handle(event);
			}
		}

		// Cada modo es responsable de regular su tiempo
		uint32_t ahora = SDL_GetTicks();
		Modo::EstadoJuego estado = modo->iteracionPrincipal(ahora - ultimo);
		if (cliente != nullptr) {
			ciclarJuego(cliente, &juego, &ultimoJuegoLeido);
			std::list<std::pair<size_t, std::string>>::iterator it;
			for(it = juego.musica.begin(); it != juego.musica.end(); ++it) {
				Sonido::Instancia()->playSound(it->second);
			}
			juego.musica.clear();
		}
//		cout << ahora - ultimo << endl;
		juego.objetivo.checkearElObjetivo(&juego.escenario.mundo);
		if (modo->estado() != Modo::EstadoJuego::aviso && juego.objetivo.objetivoEstaCumplido()) {
			modo = make_unique<Modo::Aviso>(std::move(modo), Modo::TipoAviso::Win, "");
			Sonido::Instancia()->playSound("sonidos/fvictory.wav");
			Sonido::Instancia()->playSound("sonidos/TROTIMC-Sounds/Sounds_tbv-0000000108-aplausos con silbidos.wav");
			controlador->cambiarModo(Modo::EstadoJuego::aviso);
			juego.jugadores[juego.miJugador].modoJuegoActual = Modo::EstadoJuego::aviso;
		} else if (estado != modo->estado()) {
			if (modo->estado() == Modo::EstadoJuego::aviso) {
				if (estado == Modo::EstadoJuego::simulacion || estado == Modo::EstadoJuego::visor) {
					modo = modo->transicion(estado);
					estado = Modo::EstadoJuego::edicion;
				}
			}
			modo = modo->transicion(estado);
			controlador->cambiarModo(estado);
			juego.jugadores[juego.miJugador].modoJuegoActual = estado;
		}
		SDL_Delay(5);
		ultimo = ahora;
	}
}

int mainJuego (Cliente *cliente, const char *archivoSalida)
{
	// Inicializo la SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::string mensaje("Fallo al iniciar SDL: ");
		mensaje += SDL_GetError();
		Log::Suceso(Log::FATAL, mensaje);
		return -4;
	} else {
		Log::Suceso(Log::INFO, "SDL2 iniciado correctamente.");
	}

	if (TTF_Init() != 0) {
		std::string mensaje("Fallo al iniciar SDL2_ttf: ");
		mensaje += TTF_GetError();
		Log::Suceso(Log::FATAL, mensaje);
		return -5;
	} else {
		Log::Suceso(Log::INFO, "SDL2_ttf iniciado correctamente.");
	}

	subMainJuego(cliente, archivoSalida);

	Sonido::Instancia()->limpiar();

	TTF_Quit();
	SDL_Quit();

	return 0;
}
