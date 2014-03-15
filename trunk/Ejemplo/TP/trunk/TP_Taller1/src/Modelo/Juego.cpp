#include "Juego.h"

#include <iostream>
#include <list>

namespace Modelo {

Juego::Juego ()
	: escenario()
	, jugadores()
	, musica()
	, miJugador(TipoJugador::Escenario)
	, objetivo()
	, simulando(false)
{
}

Juego::Juego (Escenario escenario,
	      std::map<TipoJugador, Jugador> jugadores,
	      std::list<std::pair<size_t, std::string>> musica,
	      TipoJugador miJugador, Objetivo objetivo, bool simulando)
	: escenario(escenario)
	, jugadores(jugadores)
	, musica(musica)
	, miJugador(miJugador)
	, objetivo(objetivo)
	, simulando(simulando)
{
}

Juego Juego::copiaProfunda ()
{
	return Juego(escenario.copiaProfunda(), jugadores, musica, miJugador, objetivo, simulando);
}

Juego& Juego::asignacionProfunda (Juego base)
{
	using std::swap;
	escenario.asignacionProfunda(base.escenario);
	for (auto& jugador : base.jugadores) {
		jugadores[jugador.first] = jugador.second;
	}
	swap(base.musica, musica);
	swap(base.miJugador, miJugador);
	swap(base.objetivo, objetivo);
	swap(base.simulando, simulando);
	return *this;
}

} /* namespace Modelo */
