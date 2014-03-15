#ifndef ITERACION_H_
#define ITERACION_H_

#include "Utils/Property.h"

template <class T>
struct AdaptadorInvierteIteracion
{
	const T& it;

	AdaptadorInvierteIteracion(T&& it) : it(it) {}

	auto begin () -> decltype(it.rbegin()) {
		return it.rbegin();
	}

	auto end () -> decltype(it.rend()) {
		return it.rend();
	}
};

template <class T>
AdaptadorInvierteIteracion<T> invertir_iteracion (T&& t)
{
	return AdaptadorInvierteIteracion<T>(t);
}

template <class Valor, class Estado>
class Iterador
{
public:
	// typedef usuales de std::iterator
	typedef std::forward_iterator_tag  iterator_category;
	typedef Property<Valor>            value_type;
	typedef long int                   difference_type;
	typedef value_type*                pointer;
	typedef value_type&                reference;

	Iterador(Estado inicial,
	         std::function<Estado(Estado)> avanzar,
	         std::function<void(Estado, Valor)> asignar,
	         std::function<Valor(Estado)> leer);

	Iterador<Valor, Estado>& operator++ ();
	Iterador<Valor, Estado> operator++ (int);
	bool operator== (Iterador<Valor, Estado> rhs);
	bool operator!= (Iterador<Valor, Estado> rhs);
	reference operator* ();
	pointer operator-> ();

private:
	std::function<Estado(Estado)> avanzar;
	std::function<void(Estado, Valor)> asignar;
	std::function<Valor(Estado)> leer;

	Estado estado;
	Property<Valor> valor;

	Property<Valor> reconstruirValor ();
};

template <class Valor, class Estado>
class Const_Iterador
{
	Iterador<Valor, Estado> base;
public:
	// typedef usuales de std::iterator
	typedef std::forward_iterator_tag  iterator_category;
	typedef const Property<Valor>      value_type;
	typedef long int                   difference_type;
	typedef value_type*                pointer;
	typedef value_type&                reference;

	Const_Iterador(Estado inicial,
	               std::function<Estado(Estado)> avanzar,
	               std::function<void(Estado, Valor)> asignar,
	               std::function<Valor(Estado)> leer)
		: base(inicial, avanzar, asignar, leer) {
	}
	Const_Iterador<Valor, Estado>& operator++ () {
		++base;
		return *this;
	}
	Const_Iterador<Valor, Estado> operator++ (int) {
		Iterador<Valor, Estado> temp = *this;
		base++;
		return temp;
	}
	bool operator== (Const_Iterador<Valor, Estado> rhs) {
		return base == rhs.base;
	}
	bool operator!= (Const_Iterador<Valor, Estado> rhs) {
		return base != rhs.base;
	}
	reference operator* () {
		return base.operator*();
	}
	pointer operator-> () {
		return base.operator->();
	}
};



// implementacion de templates


template <class Valor, class Estado>
Iterador<Valor, Estado>::Iterador(Estado inicial, std::function<Estado(Estado)> avanzar,
		std::function<void(Estado, Valor)> asignar, std::function<Valor(Estado)> leer)
	: avanzar(avanzar)
	, asignar(asignar)
	, leer(leer)
	, estado(inicial)
	, valor(reconstruirValor())
{
}

template <class Valor, class Estado>
Iterador<Valor, Estado>& Iterador<Valor, Estado>::operator++ () {
	estado = avanzar(estado);
	valor = reconstruirValor();
	return *this;
}

template <class Valor, class Estado>
Iterador<Valor, Estado> Iterador<Valor, Estado>::operator++ (int) {
	Iterador<Valor, Estado> temp = *this;
	estado = avanzar(estado);
	valor = reconstruirValor();
	return temp;
}

template <class Valor, class Estado>
bool Iterador<Valor, Estado>::operator== (Iterador<Valor, Estado> rhs) {
	return estado == rhs.estado;
}

template <class Valor, class Estado>
bool Iterador<Valor, Estado>::operator!= (Iterador<Valor, Estado> rhs) {
	return estado != rhs.estado;
}

template <class Valor, class Estado>
Property<Valor>& Iterador<Valor, Estado>::operator* () {
	return valor;
}

template <class Valor, class Estado>
Property<Valor>* Iterador<Valor, Estado>::operator-> () {
	return &valor;
}

template <class Valor, class Estado>
Property<Valor> Iterador<Valor, Estado>::reconstruirValor () {
	using namespace std::placeholders;
	std::function<Valor()> leerParcial = std::bind(leer, estado);
	std::function<void(Valor)> asignarParcial = std::bind(asignar, estado, _1);
	return Property<Valor>(leerParcial, asignarParcial);
}

#endif /* ITERACION_H_ */
