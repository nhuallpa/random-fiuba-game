#ifndef VECTOR_H_
#define VECTOR_H_

#include "Serializacion/Interno/Objeto.h"
#include <vector>

namespace Serializacion {

class Vector
{
public:
	Vector();
	Vector (const Vector&) = default;
	Vector (Vector&&) = default;
	Vector& operator= (const Vector&) = default;
	Vector& operator= (Vector&&) = default;
	~Vector() = default;

	size_t size ();
	Objeto& operator[] (unsigned indice);
	const Objeto& operator[] (unsigned indice) const;
	template <class T> void push_back (T valor);

	bool operator== (Vector) const;

	std::vector<Objeto> valores;
};

template <class T>
void Vector::push_back (T valor)
{
	valores.push_back(Objeto(valor));
}

} /* namespace Serializacion */
#endif /* VECTOR_H_ */
