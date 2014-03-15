#include "Vector.h"

namespace Serializacion {

Vector::Vector ()
	: valores()
{
}

size_t Vector::size ()
{
	return valores.size();
}

Objeto& Vector::operator[] (unsigned indice)
{
	return valores[indice];
}

const Objeto& Vector::operator[] (unsigned indice) const
{
	return valores[indice];
}

bool Vector::operator== (Vector rhs) const
{
	if (valores.size() != rhs.size()) {
		return false;
	}
	return std::equal(begin(valores), end(valores), begin(rhs.valores));
}

} /* namespace Serializacion */
