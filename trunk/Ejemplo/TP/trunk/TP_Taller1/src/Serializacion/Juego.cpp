#include "Juego.h"

#include "Serializacion/Escenario.h"
#include "Serializacion/Jugador.h"
#include "Serializacion/Interno/Mapa.h"
#include "Serializacion/Interno/Vector.h"
#include "Serializacion/Objetivo.h"

namespace Serializacion {

Objeto convertir<Modelo::Juego>::serializar (Modelo::Juego obj) {
	Mapa retval;

	retval["escenario"] = obj.escenario;

	Mapa jugadores;
	for (auto& par : obj.jugadores) {
		jugadores[Modelo::tipoJugadorToString(par.first)] = par.second;
	}
	retval["jugadores"] = jugadores;

	Vector musica;
	for (auto& par : obj.musica) {
		Mapa mapaPar;
		mapaPar["t"] = par.first;
		mapaPar["v"] = par.second;
		musica.push_back(mapaPar);
	}
	retval["musica"] = musica;
	// intencionalmente no incluyo miJugador
	retval["objetivo"] = obj.objetivo;
	retval["simulando"] = obj.simulando;

	return retval;
}

Modelo::Juego convertir<Modelo::Juego>::deserializar (const Objeto& objeto) {
	return aplicarCambios(objeto, Modelo::Juego());
}

Modelo::Juego convertir<Modelo::Juego>::aplicarCambios (const Objeto& objeto, Modelo::Juego base) {
	Modelo::Juego retval = base;

	Mapa mapa = objeto.getMapa();
	mapa.asignar_si(retval.escenario, "escenario");
	mapa.asignar_si(retval.objetivo, "objetivo");
	mapa.asignar_si(retval.simulando, "simulando");

	if (mapa.existe("jugadores")) {
		Mapa jugadores = mapa["jugadores"].getMapa();
		for (auto& par : jugadores.atributos) {
			auto clave = Modelo::stringToTipoJugador(par.first);
			if (par.second == Objeto::Borrado()) {
				retval.jugadores.erase(clave);
			} else {
				retval.jugadores[clave] = par.second;
			}
		}
	}

	if (mapa.existe("musica")) {
		retval.musica.clear();
		Vector musica = mapa["musica"].getVector();
		for (Objeto& parMusica : musica.valores) {
			size_t t = parMusica.getMapa()["t"];
			std::string v = parMusica.getMapa()["v"];
			retval.musica.push_back(std::make_pair(t, v));
		}
	}

	return retval;
}

} /* namespace Serializacion */
