#ifndef PROPERTY_H_
#define PROPERTY_H_

#include <functional>

template <class T>
class Property
{
public:
	Property (std::function<T()> leer, std::function<void(T)> asignar);
	~Property ();

	Property<T>& operator= (T valor);
	operator T ();
	operator const T () const;

private:
	std::function<T()> leer;
	std::function<void(T)> asignar;
};



// implementacion del template

template <class T>
Property<T>::Property (std::function<T()> leer, std::function<void(T)> asignar)
	: leer(leer)
	, asignar(asignar)
{
}

template <class T>
Property<T>::~Property ()
{
}

template <class T>
Property<T>& Property<T>::operator= (T valor) {
	asignar(valor);
	return *this;
}

template <class T>
Property<T>::operator T () {
	return leer();
}

template <class T>
Property<T>::operator const T () const {
	return leer();
}

#endif /* PROPERTY_H_ */
