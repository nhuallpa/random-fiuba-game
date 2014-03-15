#ifndef ATOMIC_H_
#define ATOMIC_H_

#include "Threads/Mutex.h"

namespace Threads {

template <class T>
class Atomic
{
public:
	explicit Atomic (T valorInicial = T());

	Atomic (const Atomic&) = delete;
	Atomic (Atomic&&) = default;
	Atomic& operator= (const Atomic&) = delete;
	Atomic& operator= (Atomic&&) = default;

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
	return mutex.ejecutarConLock<T>([&] {
		return valor;
	});
}

template <class T>
void Atomic<T>::transform (std::function<T(T)> fn) {
	mutex.ejecutarConLock([&] {
		valor = fn(std::move(valor));
	});
}

template <class T>
void Atomic<T>::forceSet (T nValor) {
	mutex.ejecutarConLock([&] {
		valor = nValor;
	});
}

} /* namespace Threads */
#endif /* ATOMIC_H_ */
