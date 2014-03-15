#ifndef JUEGO_H_
#define JUEGO_H_

#include "Modelo/Escenario.h"
#include "Modelo/Jugador.h"
#include <map>
#include <list>
#include "Modelo/Objetivo.h"

namespace Modelo {

struct Juego
{
	Juego ();
	Juego (Escenario escenario,
	       std::map<TipoJugador, Jugador> jugadores,
	       std::list<std::pair<size_t, std::string>> musica,
	       TipoJugador miJugador, Objetivo objetivo, bool simulando);

	Juego copiaProfunda ();
	Juego& asignacionProfunda(Juego);

	Escenario escenario;
	std::map<TipoJugador, Jugador> jugadores;
	std::list<std::pair<size_t, std::string>> musica;
	TipoJugador miJugador;
	Objetivo objetivo;
	bool simulando;
};

} /* namespace Modelo */
#endif /* JUEGO_H_ */
