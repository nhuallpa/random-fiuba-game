#include "Jugador.h"

#include "Serializacion/Rect.h"
#include "Serializacion/Vec2.h"
#include "Serializacion/FuenteMouse.h"
#include "Serializacion/Interno/Mapa.h"
#include "Serializacion/Interno/Vector.h"

namespace Serializacion {

using namespace Modelo;

Objeto convertir<Jugador>::serializar (Jugador obj) {
	Mapa retval;

	retval["jugador"] = size_t(obj.tipoJugador);
	retval["modoJuego"] = size_t(obj.modoJuegoActual);
	Mapa entidades;
	for (auto& par : obj.entidadesDisponibles) {
		entidades[tipoElementoToString(par.first)] = par.second;
	}
	retval["entidades"] = entidades;
	retval["region"] = obj.regionDeEdicion;
	retval["estadoMouse"] = size_t(obj.estadoMouse);
	retval["elementoMouse"] = size_t(obj.elementoMouse);
	if (obj.fuenteMouse != NULL)
		retval["fuenteMouse"] = obj.fuenteMouse;
	else
		retval["fuenteMouse"] = Objeto();
	retval["posicionMouse"] = obj.posicionMouse;
	retval["canvasAbsoluto"] = obj.canvasAbsoluto;

	return retval;
}

Jugador convertir<Jugador>::deserializar (const Objeto& objeto) {
	return aplicarCambios(objeto, Jugador(TipoJugador::Escenario));
}

Jugador convertir<Jugador>::aplicarCambios (const Objeto& objeto, Jugador base) {
	Jugador retval = base;
	Mapa mapa = objeto.getMapa();

	mapa.asignar_si((size_t&)retval.tipoJugador, "jugador");
	mapa.asignar_si((size_t&)retval.modoJuegoActual, "modoJuego");
	if (mapa.existe("entidades")) {
		Mapa mapaEntidades = mapa["entidades"].getMapa();
		for (auto& par : mapaEntidades.atributos) {
			auto tipo = stringToTipoElemento(par.first);
			if (par.second == Objeto::Borrado()) {
				retval.entidadesDisponibles.erase(tipo);
			} else {
				retval.entidadesDisponibles[tipo] = par.second;
			}
		}
	}
	mapa.asignar_si(retval.regionDeEdicion, "region");
	mapa.asignar_si((size_t&)retval.estadoMouse, "estadoMouse");
	mapa.asignar_si((size_t&)retval.elementoMouse, "elementoMouse");
	if (mapa.existe("fuenteMouse")) {
		if (mapa["fuenteMouse"].tipo() == Objeto::Tipo::Nulo) {
			retval.fuenteMouse = NULL;
		}
		else {
			retval.fuenteMouse = mapa["fuenteMouse"];
		}
	}
	mapa.asignar_si(retval.posicionMouse, "posicionMouse");
	mapa.asignar_si(retval.canvasAbsoluto, "canvasAbsoluto");

	return retval;
}

} /* namespace Serializacion */
