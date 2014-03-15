#include "Entidad.h"

#include "Serializacion/Vec2.h"
#include "Serializacion/Interno/Mapa.h"
#include "Serializacion/Interno/Vector.h"

namespace Serializacion {

Objeto convertir<Modelo::Entidad*>::serializar (Modelo::Entidad* rhs) {
	Mapa node;
	node["centro"] = rhs->centro;
	node["angulo"] = rhs->angulo;
	node["sentidoHorario"] = rhs->estadoNormal;
	node["idEntidadExtremoA"] = rhs->idEntidadExtremoA;
	node["idEntidadExtremoB"] = rhs->idEntidadExtremoB;
	node["puntoDeLigaduraEntidadA"] = rhs->puntoDeLigaduraEntidadA;
	node["puntoDeLigaduraEntidadB"] = rhs->puntoDeLigaduraEntidadB;
	node["accionar"] = rhs->accionar;
	node["distanciaRecorrida"] = rhs->distanciaRecorrida;
	Vector puentes;
	for (size_t id : rhs->elemPuenteAtado) {
		puentes.push_back(id);
	}
	node["elemPuenteAtado"] = puentes;
	node["jugador"] = size_t(rhs->jugador);

	auto defecto = Modelo::Entidad();
	if (rhs->id == defecto.id) {
		return node;
	}

	Mapa delta = Objeto(&defecto).getMapa().diferencia(node);
	delta["clase"] = Modelo::tipoElementoToString(rhs->clase);
	delta["id"] = rhs->id;
	delta["tamanio"] = rhs->tamanio;
	return delta;
}

Modelo::Entidad* convertir<Modelo::Entidad*>::deserializar (const Objeto& objeto) {
	using Modelo::Entidad;

	Mapa mapa = objeto.getMapa();

	size_t id = mapa.at("id");
	Modelo::TipoElemento clase = Modelo::stringToTipoElemento(mapa.at("clase"));
	Vec2 tamanio = mapa.at("tamanio");

	size_t numeroJugador = 0;
	mapa.asignar_si(numeroJugador, "jugador");
	auto jugador = Modelo::TipoJugador(numeroJugador);

	Vec2 centro;
	float angulo = 0;
	bool estadoNormal = true;
	mapa.asignar_si(centro, "centro");
	mapa.asignar_si(angulo, "angulo");
	mapa.asignar_si(estadoNormal, "sentidoHorario");

	Entidad* entidad = Entidad::maker(jugador, clase, centro, tamanio, angulo, estadoNormal, id);
	try {
		mapa.asignar_si(entidad->estadoNormal, "sentidoHorario");
		mapa.asignar_si(entidad->idEntidadExtremoA, "idEntidadExtremoA");
		mapa.asignar_si(entidad->idEntidadExtremoB, "idEntidadExtremoB");
		mapa.asignar_si(entidad->puntoDeLigaduraEntidadA, "puntoDeLigaduraEntidadA");
		mapa.asignar_si(entidad->puntoDeLigaduraEntidadB, "puntoDeLigaduraEntidadB");
		mapa.asignar_si(entidad->accionar, "accionar");
		mapa.asignar_si(entidad->distanciaRecorrida, "distanciaRecorrida");
		if (mapa.existe("elemPuenteAtado")) {
			entidad->elemPuenteAtado.clear();
			Vector vectorPuentes = mapa["elemPuenteAtado"].getVector();
			for (size_t id : vectorPuentes.valores) {
				entidad->elemPuenteAtado.push_back(id);
			}
		}
		return entidad;
	} catch (...) {
		delete entidad;
		throw std::current_exception();
	}
}

Modelo::Entidad* convertir<Modelo::Entidad*>::aplicarCambios (const Objeto& objeto, Modelo::Entidad* base) {
	Modelo::Entidad *retval = Modelo::Entidad::clonar(base);
	try {
		Mapa mapa = objeto.getMapa();

		if (mapa.existe("clase")) {
			if (Modelo::stringToTipoElemento(mapa["clase"]) != retval->clase) {
				throw Log::Suceso(Log::DEBUG, "Intento cambiar clase de entidad.");
			}
		}

		mapa.asignar_si(retval->id, "id");
		mapa.asignar_si(retval->centro, "centro");
		mapa.asignar_si(retval->tamanio, "tamanio");
		mapa.asignar_si(retval->angulo, "angulo");
		mapa.asignar_si(retval->estadoNormal, "sentidoHorario");
		mapa.asignar_si(retval->distanciaRecorrida, "distanciaRecorrida");
		mapa.asignar_si(retval->idEntidadExtremoA, "idEntidadExtremoA");
		mapa.asignar_si(retval->idEntidadExtremoB, "idEntidadExtremoB");
		mapa.asignar_si(retval->puntoDeLigaduraEntidadA, "puntoDeLigaduraEntidadA");
		mapa.asignar_si(retval->puntoDeLigaduraEntidadB, "puntoDeLigaduraEntidadB");
		mapa.asignar_si(retval->accionar, "accionar");
		mapa.asignar_si((size_t&) retval->jugador, "jugador");
		if (mapa.existe("elemPuenteAtado")) {
			retval->elemPuenteAtado.empty();
			Vector vectorPuentes = mapa["elemPuenteAtado"].getVector();
			for (size_t id : vectorPuentes.valores) {
				retval->elemPuenteAtado.push_back(id);
			}
		}
		return retval;
	} catch (...) {
		delete retval;
		throw std::current_exception();
	}
}

} /* namespace Serializacion */
