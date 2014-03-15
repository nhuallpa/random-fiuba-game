#include "Mapa.h"

namespace Serializacion {

Mapa::Mapa ()
	: atributos()
{
}

bool Mapa::existe (std::string identificador) const
{
	return atributos.count(identificador) != 0;
}

Objeto& Mapa::operator[] (std::string identificador)
{
	return atributos[identificador];
}

const Objeto& Mapa::at (std::string identificador) const
{
	if (atributos.count(identificador) != 0) {
		return atributos.at(identificador);
	} else {
		throw Log::Suceso(Log::ERROR, "Accedo a valor inexistente en Mapa.");
	}
}

Mapa Mapa::diferencia (Mapa resultado) const
{
	Mapa retval;
	auto base = begin(atributos);
	auto final = begin(resultado.atributos);

	while (base != end(atributos) && final != end(resultado.atributos)) {
		if (base->first == final->first) {
			if (!(base->second == final->second)) {
				retval[final->first] = base->second.diferencia(final->second);
			}
			std::advance(base, 1);
			std::advance(final, 1);
		} else if (base->first < final->first) {
			retval[base->first] = Objeto::Borrado();
			std::advance(base, 1);
		} else {
			retval[final->first] = final->second;
			std::advance(final, 1);
		}
	}
	while (base != end(atributos)) {
		retval[base->first] = Objeto::Borrado();
		std::advance(base, 1);
	}
	while (final != end(resultado.atributos)) {
		retval[final->first] = final->second;
		std::advance(final, 1);
	}

	return retval;
}

Mapa Mapa::aplicar (Mapa diff) const
{
	Mapa retval;
	auto base = begin(atributos);
	auto final = begin(diff.atributos);

	while (base != end(atributos) && final != end(diff.atributos)) {
		if (base->first == final->first) {
			if (final->second != Objeto::Borrado()) {
				retval[final->first] = base->second.aplicar(final->second);
			}
			std::advance(base, 1);
			std::advance(final, 1);
		} else if (base->first < final->first) {
			retval[base->first] = base->second;
			std::advance(base, 1);
		} else {
			if (final->second != Objeto::Borrado()) {
				retval[final->first] = final->second;
			}
			std::advance(final, 1);
		}
	}
	while (base != end(atributos)) {
		retval[base->first] = base->second;
		std::advance(base, 1);
	}
	while (final != end(diff.atributos)) {
		if (final->second != Objeto::Borrado()) {
			retval[final->first] = final->second;
		}
		std::advance(final, 1);
	}

	return retval;
}

bool Mapa::operator== (Mapa rhs) const
{
	if (atributos.size() != rhs.atributos.size()) {
		return false;
	}
	return std::equal(begin(atributos), end(atributos), begin(rhs.atributos));
}

} /* namespace Serializacion */
