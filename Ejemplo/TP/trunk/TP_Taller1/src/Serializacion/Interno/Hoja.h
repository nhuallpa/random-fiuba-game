#ifndef HOJA_H_
#define HOJA_H_

#include "Log/Suceso.h"
#include "Serializacion/Interno/HojaImpl.h"
#include "Utils/make_unique.h"

namespace Serializacion {

class Hoja
{
public:
	Hoja ();
	Hoja (const Hoja&);
	Hoja (Hoja&&);
	Hoja& operator= (Hoja);
	~Hoja ();

	std::string aYaml () const;
	static Hoja deYaml (std::string valor);
	std::vector<uint8_t> aRed () const;
	static Hoja deRed (const std::vector<uint8_t>&, unsigned& inicio);

	template <class T> explicit Hoja (T valor);
	template <class T> T valor ();

	bool operator== (Hoja) const;

	Hoja_ImplBase* impl;
};


// implementacion de templates

template <class T>
Hoja::Hoja (T valor)
	: impl()
{
	auto ptr = new Hoja_Impl<T>();
	ptr->valor = valor;
	impl = ptr;
}

template <class T>
T Hoja::valor ()
{
	auto ptr = dynamic_cast<Hoja_Impl<T>*>(impl);
	if (ptr == nullptr) {
		throw Log::Suceso(Log::DEBUG, "Error de tipo al deserializar hoja.");
	}
	return ptr->valor;
}

} /* namespace Serializacion */
#endif /* HOJA_H_ */
