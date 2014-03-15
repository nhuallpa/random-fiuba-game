#include "Entidad.h"

#include "Modelo/Interno/Balancin.h"
#include "Modelo/Interno/EntidadCorreable.h"
#include "Modelo/Interno/EntidadElementoPuente.h"
#include "Modelo/Interno/Gancho.h"
#include "Modelo/Interno/Globo.h"
#include "Modelo/Interno/Polea.h"
#include "Modelo/Interno/Tijera.h"
#include "Modelo/Interno/Yunque.h"
#include "Modelo/Interno/Carrito.h"

#include "Log/Suceso.h"
#include <algorithm>

namespace Modelo {

Entidad::Entidad()
	: id(0)
	, clase()
	, centro()
	, tamanio()
	, angulo()
	, estadoNormal(true)
	, distanciaRecorrida(0)
	, idEntidadExtremoA(0)
	, idEntidadExtremoB(0)
	, puntoDeLigaduraEntidadA()
	, puntoDeLigaduraEntidadB()
	, accionar(false)
	, elemPuenteAtado()
	, jugador(TipoJugador::Escenario)
{
}


Entidad::Entidad(TipoJugador jugador, Modelo::TipoElemento clase, Vec2 centro,
		Vec2 tamanio, float angulo, bool estadoNormal, unsigned int id)
	: id(id)
	, clase(clase)
	, centro(centro)
	, tamanio(tamanio)
	, angulo(angulo)
	, estadoNormal(estadoNormal)
	, distanciaRecorrida(0)
	, idEntidadExtremoA(0)
	, idEntidadExtremoB(0)
	, puntoDeLigaduraEntidadA()
	, puntoDeLigaduraEntidadB()
	, accionar(false)
	, elemPuenteAtado()
	, jugador(jugador)
{
}

Entidad* Entidad::maker(TipoJugador jugador, TipoElemento clase, Vec2 centro,
                        Vec2 tamanio, float angulo, bool estadoNormal, unsigned int id)
{
	switch (clase) {
	case TipoElemento::Canio:
	case TipoElemento::Clavo:
	case TipoElemento::Codo:
	case TipoElemento::Huevo:
	case TipoElemento::PaletaFlipper:
	case TipoElemento::PelotaBasquet:
	case TipoElemento::PelotaBowling:
	case TipoElemento::Domino:
	case TipoElemento::Plataforma:
	case TipoElemento::Vela:
	case TipoElemento::Queso:
	case TipoElemento::Canasto:
		return new Entidad(jugador, clase, centro, tamanio, angulo, estadoNormal, id);

	case TipoElemento::Motor:
	case TipoElemento::Engranaje:
	case TipoElemento::CintaTransportadora:
	case TipoElemento::MotorRaton:
		return new EntidadCorreable(jugador, clase, centro, tamanio, angulo, estadoNormal, id);

	case TipoElemento::Soga:
	case TipoElemento::Correa:
		return new EntidadElementoPuente(jugador, clase, centro, tamanio, angulo, estadoNormal, id);

	case TipoElemento::Globo:
		return new Globo(jugador, clase, centro, tamanio, angulo, estadoNormal, id);

	case TipoElemento::Balancin:
		return new Balancin(jugador, clase, centro, tamanio, angulo, estadoNormal, id);

	case TipoElemento::Yunque:
		return new Yunque(jugador, clase, centro, tamanio, angulo, estadoNormal, id);

	case TipoElemento::Gancho:
		return new Gancho(jugador, clase, centro, tamanio, angulo, estadoNormal, id);

	case TipoElemento::Tijera:
		return new Tijera(jugador, clase, centro, tamanio, angulo, estadoNormal, id);

	case TipoElemento::Polea:
		return new Polea(jugador, clase, centro, tamanio, angulo, estadoNormal, id);

	case TipoElemento::Carrito:
		return new Carrito(jugador, clase, centro, tamanio, angulo, estadoNormal, id);
	}
	throw Log::Suceso(Log::DEBUG, "Entidad de tipo invalido.");
}

Entidad* Entidad::clonar (Entidad *base)
{
	Entidad *retval = maker(base->jugador, base->clase, base->centro, base->tamanio,
			base->angulo, base->estadoNormal, base->id);
	retval->distanciaRecorrida = base->distanciaRecorrida;
	retval->elemPuenteAtado = base->elemPuenteAtado;
	retval->idEntidadExtremoA = base->idEntidadExtremoA;
	retval->idEntidadExtremoB = base->idEntidadExtremoB;
	retval->puntoDeLigaduraEntidadA = base->puntoDeLigaduraEntidadA;
	retval->puntoDeLigaduraEntidadB = base->puntoDeLigaduraEntidadB;
	retval->accionar = base->accionar;
	return retval;
}

Entidad::~Entidad () {
}


bool Entidad::colicionaCon(Entidad* otraEntidad) const {
	if (esElementoPuente(clase) || esElementoPuente(otraEntidad->clase)) {
		return false;
	}

	Vec2 tamOtroSup;
	Vec2 tamMiSup;

	// Solo se aplica el porcentaje permitido de colisión si se juntan engranajes
	// TODO mover a métodos virtuales de correa y engranaje.
	if ((this->clase == Modelo::TipoElemento::Engranaje && otraEntidad->clase == Modelo::TipoElemento::Engranaje) ||
			(this->clase == Modelo::TipoElemento::CintaTransportadora && otraEntidad->clase == Modelo::TipoElemento::Engranaje) ||
			(this->clase == Modelo::TipoElemento::Engranaje && otraEntidad->clase == Modelo::TipoElemento::CintaTransportadora) ) {
		tamOtroSup = otraEntidad->tamanio - otraEntidad->tamanio*PORCENTAJE_PERMITIDO_COLISION/100;
		tamMiSup = tamanio - tamanio*PORCENTAJE_PERMITIDO_COLISION/100;
	}
	else {
		tamOtroSup = otraEntidad->tamanio;
		tamMiSup = tamanio;
	}

	Rect otroSup = Rect::deCentro(otraEntidad->centro, tamOtroSup);
	Rect miSup = Rect::deCentro(centro, tamMiSup);

	return miSup.colisiona(angulo, otroSup, otraEntidad->angulo);
}


bool Entidad::tieneElemPuenteAtado() const {
	if (!this->elemPuenteAtado.empty()) {
		return true;
	}
	return false;
}


std::vector<Vec2> Entidad::puntoLigadura() const {
	auto retval = puntoLigaduraLocal();
	for (auto& val : retval) {
		val = centro + val.rotar(angulo);
	}
	return retval;
}


std::vector<Vec2> Entidad::puntoLigaduraLocal() const {
	return std::vector<Vec2>();
}


std::pair<bool, Vec2> Entidad::lugarUnionMasCercano(Vec2 pos) const {
	auto candidatos = puntoLigadura();
	if (candidatos.empty()) {
		return std::make_pair(false, Vec2());
	}
	Vec2 val = *std::min_element(begin(candidatos), end(candidatos), [pos] (Vec2 lhs, Vec2 rhs) {
		return lhs.distancia(pos) < rhs.distancia(pos);
	});
	return std::make_pair(true, val);
}

void Entidad::regenerar () {
	centro = (puntoDeLigaduraEntidadA + puntoDeLigaduraEntidadB) / 2;
	tamanio.x = puntoDeLigaduraEntidadA.distancia(puntoDeLigaduraEntidadB);
	angulo = puntoDeLigaduraEntidadA.anguloCon(puntoDeLigaduraEntidadB);
}


} /* namespace Modelo */
