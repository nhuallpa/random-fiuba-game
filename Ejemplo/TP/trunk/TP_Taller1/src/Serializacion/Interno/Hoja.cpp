#include "Hoja.h"

namespace Serializacion {

Hoja::Hoja ()
	: impl(nullptr)
{
}

Hoja::Hoja (const Hoja& base)
	: impl(base.impl->clonar())
{
}

Hoja::Hoja (Hoja&& base)
	: impl(base.impl)
{
	base.impl = nullptr;
}

Hoja& Hoja::operator= (Hoja base)
{
	using std::swap;
	swap(base.impl, impl);
	return *this;
}

Hoja::~Hoja()
{
	delete impl;
}

std::string Hoja::aYaml () const
{
	return impl->aYaml();
}

Hoja Hoja::deYaml (std::string valor)
{
	Hoja hoja;
	hoja.impl = Hoja_ImplBase::deYaml(valor);
	return hoja;
}

std::vector<uint8_t> Hoja::aRed () const
{
	return impl->aRed();
}

Hoja Hoja::deRed (const std::vector<uint8_t>& origen, unsigned& inicio)
{
	Hoja hoja;
	hoja.impl = Hoja_ImplBase::deRed(origen, inicio);
	return hoja;
}

bool Hoja::operator== (Hoja rhs) const
{
	if (impl == rhs.impl) {
		return true;
	}
	if (typeid(*impl) != typeid(*rhs.impl)) {
		return false;
	}
	return impl->equals(rhs.impl);
}

} /* namespace Serializacion */
