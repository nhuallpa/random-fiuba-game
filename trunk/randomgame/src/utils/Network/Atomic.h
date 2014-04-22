#ifndef ATOMIC_H_
#define ATOMIC_H_

#include "Mutex.h"

template <class T>
class Atomic
{
public:
	explicit Atomic (T valorInicial = T());
	T get () const;
	void transform (std::function<T(T)> fn);
	void forceSet (T valor);

	typedef T value_type;

private:
	mutable Mutex mutex;
	T valor;
};


// implementacion del template
template <class T>
Atomic<T>::Atomic (T valorInicial)
	: mutex()
	, valor(std::move(valorInicial))
{
}

template <class T>
T Atomic<T>::get () const {
	return mutex.saferun<T>([&] {
		return valor;
	});
}

template <class T>
void Atomic<T>::transform (std::function<T(T)> fn) {
	mutex.saferun([&] {
		valor = fn(std::move(valor));
	});
}

template <class T>
void Atomic<T>::forceSet (T nValor) {
	mutex.saferun([&] {
		valor = nValor;
	});
}

#endif /* ATOMIC_H_ */
