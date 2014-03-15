#include "Mundo.h"

#include "Log/Suceso.h"
#include "Modelo/TipoElemento.h"
#include "Modelo/Interno/Entidad.h"
#include "Modelo/Interno/MundoBase.h"
#include "Utils/Vec2.h"
#include "Utils/Rect.h"
#include <cstddef>

namespace Modelo {

Mundo::Mundo()
	: base(std::make_shared<MundoBase>())
	, validaColisiones_(true)
{
}

Mundo Mundo::copiaProfunda ()
{
	Mundo retval;
	retval.base = std::make_shared<MundoBase>(*base);
	retval.validaColisiones_ = validaColisiones_;
	return retval;
}

Mundo& Mundo::asignacionProfunda (Mundo original)
{
	*base = std::move(*original.base);
	validaColisiones_ = original.validaColisiones_;
	return *this;
}

EntidadWrapper Mundo::agregarEntidad (TipoJugador jugador, TipoElemento clase, Vec2 centro,
                                      Vec2 tamanio, float angulo, bool estadoNormal)
{
	Entidad *nuevaEntidad = Entidad::maker(jugador, clase, centro, tamanio, angulo, estadoNormal, 0);
	size_t id = base->agregar(std::unique_ptr<Entidad>(nuevaEntidad), validaColisiones_);
	return EntidadWrapper(id, base);
}

EntidadWrapper Mundo::agregarEntidad (TipoJugador jugador, TipoElemento clase,
                                      EntidadWrapper vinculadoA, EntidadWrapper vinculadoB,
                                      Vec2 posVinculoA, Vec2 posVinculoB, float alto)
{
	Entidad *nuevaEntidad = Entidad::maker(jugador, clase, Vec2(), Vec2(0, alto), 0, true, 0);
	size_t id = base->agregar(std::unique_ptr<Entidad>(nuevaEntidad), validaColisiones_);
	EntidadWrapper retval = EntidadWrapper(id, base);
	retval.vincular(vinculadoA, vinculadoB, posVinculoA, posVinculoB);
	return retval;
}

bool Mundo::comprobarUnion(EntidadWrapper lhs, EntidadWrapper rhs, Vec2 a, Vec2 b) {
	if (!lhs.valido() || !rhs.valido()) {
		throw Log::Suceso(Log::DEBUG, "Vinculo entre entidades nulas");
	}
	auto infoA = lhs.base()->lugarUnionMasCercano(a);
	auto infoB = rhs.base()->lugarUnionMasCercano(b);
	if (!infoA.first || !infoB.first) {
		return false;
	}
	auto puntoUnionUsado = [&] (EntidadWrapper ent, Vec2 punto) -> bool {
		for (size_t idVinculo : ent.base()->elemPuenteAtado) {
			auto vinculo = buscarElemento(idVinculo);
			if (vinculo.puntoDeLigaduraEntidadA() == punto ||
				vinculo.puntoDeLigaduraEntidadB() == punto) {
				return true;
			}
		}
		return false;
	};
	if (puntoUnionUsado(lhs, infoA.second) || puntoUnionUsado(rhs, infoB.second)) {
		return false;
	}

	return true;
}

EntidadWrapper Mundo::agregarEntidad (Entidad* nuevaEntidad)
{
	size_t id = base->agregar(std::unique_ptr<Entidad>(nuevaEntidad), validaColisiones_);
	return EntidadWrapper(id, base);
}

void Mundo::quitarEntidad (size_t id) {
	base->quitar(id);
}

void Mundo::quitarEntidad (EntidadWrapper unaEntidad) {
	base->quitar(unaEntidad.id());
}

Mundo::iterator Mundo::construirIterador (Mundo::base_iterador estadoConstruir) {
	return Iterador<EntidadWrapper, Mundo::base_iterador>(
			estadoConstruir,
			[&] (Mundo::base_iterador estado) -> Mundo::base_iterador {
				return ++estado;},
			[&] (Mundo::base_iterador estado, EntidadWrapper valor) {
				},
			[&] (Mundo::base_iterador estado) -> EntidadWrapper {
				return EntidadWrapper(estado->first, base);}
	);
}

Mundo::const_iterator Mundo::construirConstIterador (Mundo::base_const_iterador estadoConstruir) const {
	return Const_Iterador<EntidadWrapper, Mundo::base_const_iterador>(
			estadoConstruir,
			[&] (Mundo::base_const_iterador estado) -> Mundo::base_const_iterador {
				return ++estado;},
			[&] (Mundo::base_const_iterador estado, EntidadWrapper valor) {
				},
			[&] (Mundo::base_const_iterador estado) -> EntidadWrapper {
				return EntidadWrapper(estado->first, base);}
	);
}

Mundo::iterator Mundo::begin () {
	return construirIterador(base->contenido.begin());
}

Mundo::iterator Mundo::end () {
	return construirIterador(base->contenido.end());
}

Mundo::const_iterator Mundo::cbegin () const {
	return construirConstIterador(base->contenido.cbegin());
}

Mundo::const_iterator Mundo::cend() const {
	return construirConstIterador(base->contenido.cend());
}

Mundo::const_iterator Mundo::begin () const {
	return cbegin();
}

Mundo::const_iterator Mundo::end() const {
	return cend();
}

bool Mundo::colicionaConAlgo(EntidadWrapper unaEntidad) {

	if (unaEntidad.esElementoPuente()) {
		return false;
	}

	for (auto& entidad : base->contenido) {
		if (unaEntidad.base()->colicionaCon(entidad.second.get())) {
			return true;
		}
	}
	return false;
}

EntidadWrapper Mundo::buscarElemento(unsigned id) {
	if (base->existe(id)) {
		return EntidadWrapper(id, base);
	}
	return EntidadWrapper();
}

EntidadWrapper Mundo::buscarElemento(Vec2 punto) {
	for (auto& par : base->contenido) {
		Entidad *entidad = par.second.get();
		Rect sup = Rect::deCentro(entidad->centro, entidad->tamanio);
		if (sup.contiene(punto, entidad->angulo)) {
			return EntidadWrapper(entidad->id, base);
		}
	}
	return EntidadWrapper();
}

bool& Mundo::validaColisiones () {
	return validaColisiones_;
}

bool Mundo::validaColisiones () const {
	return validaColisiones_;
}

} /* namespace Modelo */
