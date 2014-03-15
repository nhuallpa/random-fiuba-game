#include "Objeto.h"

#include "Serializacion/Interno/Hoja.h"
#include "Serializacion/Interno/Mapa.h"
#include "Serializacion/Interno/Vector.h"
#include "Serializacion/YAML/Objeto.h"
#include <string>
#include <sstream>
#include <utility>
#include <yaml-cpp/yaml.h>

namespace Serializacion {

Objeto::Objeto ()
	: tipo_(Tipo::Nulo)
	, dato()
{
}

Objeto Objeto::Borrado ()
{
	Objeto retval;
	retval.tipo_ = Tipo::Borrado;
	return retval;
}

Objeto::Objeto (Hoja hoja)
	: tipo_(Tipo::Hoja)
	, dato(new Hoja(std::move(hoja)))
{
}

Objeto::Objeto (Mapa mapa)
	: tipo_(Tipo::Mapa)
	, dato(new Mapa(std::move(mapa)))
{
}

Objeto::Objeto (Vector vector)
	: tipo_(Tipo::Vector)
	, dato(new Vector(std::move(vector)))
{
}

static void error (Objeto::Tipo deseado, Objeto::Tipo dado)
{
	std::map<Objeto::Tipo, std::string> conv = {
		{Objeto::Tipo::Borrado, "borrado"},
		{Objeto::Tipo::Hoja, "hoja"},
		{Objeto::Tipo::Mapa, "mapa"},
		{Objeto::Tipo::Vector, "vector"},
		{Objeto::Tipo::Nulo, "nulo"},
	};
	std::string mensaje = std::string("Intento convertir ")
	                    + conv[dado] + " en " + conv[deseado] + ".";
	throw Log::Suceso(Log::ERROR, mensaje);
}

Hoja Objeto::getHoja () const
{
	if (tipo_ != Tipo::Hoja) {
		error(Tipo::Hoja, tipo_);
	}
	return *static_cast<Hoja*>(dato.get());
}

Mapa Objeto::getMapa () const
{
	if (!casteable(Tipo::Mapa)) {
		error(Tipo::Mapa, tipo_);
	}
	if (tipo_ != Tipo::Mapa) {
		return Mapa();
	}
	return *static_cast<Mapa*>(dato.get());
}

Vector Objeto::getVector () const
{
	if (!casteable(Tipo::Vector)) {
		error(Tipo::Vector, tipo_);
	}
	if (tipo_ != Tipo::Vector) {
		return Vector();
	}
	return *static_cast<Vector*>(dato.get());
}

Objeto::Tipo Objeto::tipo () const
{
	return tipo_;
}

bool Objeto::casteable (Objeto::Tipo tipo) const
{
	switch (tipo) {
	case Tipo::Borrado:
	case Tipo::Hoja:
		return tipo_ == tipo;

	case Tipo::Mapa:
	case Tipo::Vector:
		return tipo_ == tipo || casteable(Tipo::Nulo);

	case Tipo::Nulo:
		if (tipo_ == Tipo::Mapa) {
			return getMapa().atributos.empty();
		} else if (tipo_ == Tipo::Vector) {
			return getVector().valores.empty();
		} else {
			return tipo_ == Tipo::Nulo;
		}
	}
	return false;
}

std::vector<uint8_t> Objeto::aRed () const
{
	std::vector<uint8_t> retval;
	auto extender = [&] (std::vector<uint8_t> extra) {
		retval.insert(end(retval), begin(extra), end(extra));
	};

	switch (tipo_) {
	case Tipo::Hoja:
		extender(getHoja().aRed());
		break;

	case Tipo::Mapa:
		{
			Mapa mapa = getMapa();
			retval.push_back('M');
			extender(Hoja(mapa.atributos.size()).aRed());
			for (auto& par : mapa.atributos) {
				extender(Hoja(par.first).aRed());
				extender(par.second.aRed());
			}
		}
		break;

	case Tipo::Borrado:
		retval.push_back('D');
		break;

	case Tipo::Nulo:
		retval.push_back('N');
		break;

	case Tipo::Vector:
		{
			Vector vector = getVector();
			retval.push_back('V');
			extender(Hoja(vector.valores.size()).aRed());
			for (auto& val : getVector().valores) {
				extender(val.aRed());
			}
		}
		break;
	}

	return retval;
}

Objeto Objeto::deRed (std::vector<uint8_t> base)
{
	unsigned int inicio = 0;
	return Objeto::deRed(std::move(base), inicio);
}

Objeto Objeto::deRed (std::vector<uint8_t> base, unsigned& inicio)
{
	switch (base[inicio++]) {
	case 'T':
	case 'F':
	case 'u':
	case 'f':
	case 's':
		return Hoja::deRed(base, --inicio);
	case 'M':
		{
			Mapa retval;
			size_t tam = Hoja::deRed(base, inicio).valor<size_t>();
			for (size_t i = 0; i < tam; ++i) {
				std::string clave = Hoja::deRed(base, inicio).valor<std::string>();
				Objeto valor = Objeto::deRed(base, inicio);
				retval[clave] = valor;
			}
			return retval;
		}
		break;
	case 'D':
		return Objeto::Borrado();
	case 'N':
		return Objeto();
	case 'V':
		{
			Vector retval;
			size_t tam = Hoja::deRed(base, inicio).valor<size_t>();
			for (size_t i = 0; i < tam; ++i) {
				retval.push_back(Objeto::deRed(base, inicio));
			}
			return retval;
		}
		break;
	}
	throw Log::Suceso(Log::ERROR, "Objeto de tipo invalido en red.");
}

std::string Objeto::to_string() const
{
	YAML::Node nodo(*this);
	std::stringstream out;
	out << nodo << std::endl;
	return out.str();
}

Objeto Objeto::diferencia (Objeto final) const
{
	if (casteable(Tipo::Mapa) && final.casteable(Tipo::Mapa)) {
		return getMapa().diferencia(final.getMapa());
	}
	return final;
}

Objeto Objeto::aplicar (Objeto diff) const
{
	Objeto retval = *this;

	if (casteable(Tipo::Mapa) && diff.casteable(Tipo::Mapa)) {
		retval = getMapa().aplicar(diff.getMapa());
	} else if (diff.casteable(Tipo::Borrado)) {
		throw Log::Suceso(Log::DEBUG, "Borrado en mala ubicacion");
	} else {
		retval = std::move(diff);
	}
	return retval;
}

bool Objeto::operator== (Objeto obj) const
{
	switch (tipo_) {
	case Tipo::Hoja:
		if (obj.casteable(Tipo::Hoja)) {
			return getHoja() == obj.getHoja();
		}
		return false;

	case Tipo::Mapa:
		if (obj.casteable(Tipo::Mapa)) {
			return getMapa() == obj.getMapa();
		}
		return false;

	case Tipo::Vector:
		if (obj.casteable(Tipo::Vector)) {
			return getVector() == obj.getVector();
		}
		return false;

	case Tipo::Borrado:
	case Tipo::Nulo:
		return obj.casteable(tipo_);
	}
	throw Log::Suceso(Log::DEBUG, "Objeto de tipo invalido.");
}

bool Objeto::operator!= (Objeto obj) const
{
	return !(*this == std::move(obj));
}

} /* namespace Serializacion */
