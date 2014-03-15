#include "EntidadWrapper.h"

#include "Log/Suceso.h"
#include "Modelo/Interno/Entidad.h"
#include "Modelo/Interno/MundoBase.h"
#include "Utils/make_unique.h"
#include "Utils/Vec2.h"

namespace Modelo {


EntidadWrapper::EntidadWrapper()
	: id_(0)
	, mundo()
{
}

EntidadWrapper::EntidadWrapper(EntidadWrapper&& original)
	: id_(original.id_)
	, mundo(original.mundo)
{
}

EntidadWrapper& EntidadWrapper::operator= (EntidadWrapper original)
{
	using std::swap;
	swap(id_, original.id_);
	swap(mundo, original.mundo);
	return *this;
}

bool EntidadWrapper::colicionaCon(EntidadWrapper otraEntidad) const
{
	return mundo.lock()->colisionan(id_, otraEntidad.id_);
}

bool EntidadWrapper::esMovil() const
{
	return Modelo::esMovil(clase());
}

bool EntidadWrapper::esNoMovil() const
{
	return Modelo::esNoMovil(clase());
}

bool EntidadWrapper::esElementoPuente() const
{
	return Modelo::esElementoPuente(clase());
}

bool EntidadWrapper::esSogeable() const
{
	return Modelo::esSogeable(clase());
}

bool EntidadWrapper::esCorreable() const
{
	return Modelo::esCorreable(clase());
}

bool EntidadWrapper::esInteractiva() const
{
	return esInteractivo(clase());
}

bool EntidadWrapper::esAtravesable() const
{
	return Modelo::esAtravesable(clase());
}

bool EntidadWrapper::vincular(EntidadWrapper lhs, EntidadWrapper rhs, Vec2 a, Vec2 b)
{
	if (!esElementoPuente()) {
		throw Log::Suceso(Log::DEBUG, "Vinculo con mala clase");
	}
	if (!lhs.valido() || !rhs.valido()) {
		throw Log::Suceso(Log::DEBUG, "Vinculo entre entidades nulas");
	}

	auto infoA = lhs.base()->lugarUnionMasCercano(a);
	auto infoB = rhs.base()->lugarUnionMasCercano(b);

	lhs.base()->elemPuenteAtado.push_back(id_);
	rhs.base()->elemPuenteAtado.push_back(id_);
	base()->puntoDeLigaduraEntidadA = infoA.second;
	base()->puntoDeLigaduraEntidadB = infoB.second;
	base()->idEntidadExtremoA = lhs.id_;
	base()->idEntidadExtremoB = rhs.id_;
	base()->regenerar();
	return true;
}

bool EntidadWrapper::tieneElemPuenteAtado() const
{
	return base()->tieneElemPuenteAtado();
}

std::vector<Vec2> EntidadWrapper::lugarDondeSePuedeUnir() const
{
	return base()->puntoLigadura();
}

std::list<EntidadWrapper> EntidadWrapper::desenlazarElemPuente()
{
	std::list<size_t> original;
	std::swap(base()->elemPuenteAtado, original);
	std::list<EntidadWrapper> retval;
	for (size_t id : original) {
		retval.push_back(EntidadWrapper(id, mundo));
	}
	return retval;
}

bool EntidadWrapper::operator== (EntidadWrapper rhs) const
{
	if (!valido() && !rhs.valido()) {
		return true;
	}
	if (!valido() || !rhs.valido()) {
		return false;
	}

	if (mundo.lock().get() != rhs.mundo.lock().get()) {
		return false;
	}
	return id_ == rhs.id_;
}

bool EntidadWrapper::operator< (EntidadWrapper rhs) const
{
	if (!valido() && !rhs.valido()) {
		return true;
	}
	if (!valido() || !rhs.valido()) {
		return false;
	}

	if (mundo.lock().get() < rhs.mundo.lock().get()) {
		return false;
	}
	return id_ < rhs.id_;
}

bool EntidadWrapper::operator> (EntidadWrapper rhs) const
{
	if (!valido() && !rhs.valido()) {
		return true;
	}
	if (!valido() || !rhs.valido()) {
		return false;
	}

	if (mundo.lock().get() < rhs.mundo.lock().get()) {
		return false;
	}
	return id_ > rhs.id_;
}

Modelo::TipoElemento& EntidadWrapper::clase()
{
	return base()->clase;
}

Vec2& EntidadWrapper::centro()
{
	return base()->centro;
}

Vec2& EntidadWrapper::tamanio()
{
	return base()->tamanio;
}

float& EntidadWrapper::angulo()
{
	return base()->angulo;
}

EntidadWrapper EntidadWrapper::entidadExtremoA()
{
	return EntidadWrapper(base()->idEntidadExtremoA, mundo);
}

EntidadWrapper EntidadWrapper::entidadExtremoB()
{
	return EntidadWrapper(base()->idEntidadExtremoB, mundo);
}

Vec2& EntidadWrapper::puntoDeLigaduraEntidadA()
{
	return base()->puntoDeLigaduraEntidadA;
}

Vec2& EntidadWrapper::puntoDeLigaduraEntidadB()
{
	return base()->puntoDeLigaduraEntidadB;
}

std::list<EntidadWrapper> EntidadWrapper::elemPuenteAtado()
{
	std::list<size_t> original = base()->elemPuenteAtado;
	std::list<EntidadWrapper> retval;
	for (size_t id : original) {
		retval.push_back(EntidadWrapper(id, mundo));
	}
	return retval;
}

Modelo::TipoElemento EntidadWrapper::clase() const
{
	return base()->clase;
}

Vec2 EntidadWrapper::centro() const
{
	return base()->centro;
}

Vec2 EntidadWrapper::tamanio() const
{
	return base()->tamanio;
}

float EntidadWrapper::angulo() const
{
	return base()->angulo;
}

float EntidadWrapper::radio() const
{
	return std::max(base()->tamanio.x, base()->tamanio.y) / 2;
}

float& EntidadWrapper::distanciaRecorrida ()
{
	return base()->distanciaRecorrida;
}

float EntidadWrapper::distanciaRecorrida () const
{
	return base()->distanciaRecorrida;
}

const EntidadWrapper EntidadWrapper::entidadExtremoA() const
{
	return EntidadWrapper(base()->idEntidadExtremoA, mundo);
}

const EntidadWrapper EntidadWrapper::entidadExtremoB() const
{
	return EntidadWrapper(base()->idEntidadExtremoB, mundo);
}

Vec2 EntidadWrapper::puntoDeLigaduraEntidadA() const
{
	return base()->puntoDeLigaduraEntidadA;
}

Vec2 EntidadWrapper::puntoDeLigaduraEntidadB() const
{
	return base()->puntoDeLigaduraEntidadB;
}

const std::list<EntidadWrapper> EntidadWrapper::elemPuenteAtado() const
{
	std::list<size_t> original = base()->elemPuenteAtado;
	std::list<EntidadWrapper> retval;
	for (size_t id : original) {
		retval.push_back(EntidadWrapper(id, mundo));
	}
	return retval;
}

bool& EntidadWrapper::estadoNormal()
{
	return base()->estadoNormal;
}

bool EntidadWrapper::estadoNormal() const
{
	return base()->estadoNormal;
}

bool& EntidadWrapper::accionar()
{
	return base()->accionar;
}

bool EntidadWrapper::accionar() const
{
	return base()->accionar;
}

TipoJugador& EntidadWrapper::jugador() {
	return base()->jugador;
}

TipoJugador EntidadWrapper::jugador() const {
	return base()->jugador;
}

size_t EntidadWrapper::id() const {
	return id_;
}

bool EntidadWrapper::valido() const {
	return id_ != 0 && !mundo.expired() && mundo.lock()->existe(id_);
}

void EntidadWrapper::borrar() {
	mundo.lock()->quitar(id_);
}

void EntidadWrapper::regenerar ()
{
	base()->regenerar();
}

EntidadWrapper::EntidadWrapper (size_t id_, std::weak_ptr<MundoBase> mundo)
	: id_(id_)
	, mundo(mundo)
{
}

Entidad *EntidadWrapper::base ()
{
	if (!valido()) {
		throw Log::Suceso(Log::DEBUG, "Intento acceder a entidad sin mundo.");
	}
	return mundo.lock()->at(id_);
}

const Entidad *EntidadWrapper::base () const
{
	if (!valido()) {
		throw Log::Suceso(Log::DEBUG, "Intento acceder a entidad sin mundo.");
	}
	return mundo.lock()->at(id_);
}

} /* namespace Modelo */
