#ifndef CONVERTIR_H_
#define CONVERTIR_H_

#include "HojaImpl.h"

namespace Serializacion {

class Objeto;

template <class T, bool basico = Hoja_Impl<T>::basico>
struct convertir
{
	static Objeto serializar (T obj);
	static T aplicarCambios (const Objeto& objeto, T base);
	static T deserializar (const Objeto& objeto);
};
} /* namespace Serializacion */

#include "Objeto.h"
#include "Hoja.h"

namespace Serializacion {

template <class T>
struct convertir<T, true>
{
	static Objeto serializar (T obj) {
		return Objeto(Hoja(obj));
	}
	static T aplicarCambios (const Objeto& objeto, T base) {
		return objeto.getHoja().valor<T>();
	}
	static T deserializar (const Objeto& objeto) {
		return objeto.getHoja().valor<T>();
	}
};

template <class T, bool basico>
Objeto convertir<T, basico>::serializar (T obj) {
	static_assert(sizeof(T) < 0, "Falta definir o incluir una especializacion "
			"de Serializacion::convertir::serializar");
	return Objeto();
}

template <class T, bool basico>
T convertir<T, basico>::aplicarCambios (const Objeto& objeto, T base) {
	static_assert(sizeof(T) < 0, "Falta definir o incluir una especializacion "
			"de Serializacion::convertir::aplicarCambios");
	return T();
}

template <class T, bool basico>
T convertir<T, basico>::deserializar (const Objeto& objeto) {
	static_assert(sizeof(T) < 0, "Falta definir o incluir una especializacion "
			"de Serializacion::convertir::deserializar");
	return T();
}

template <>
struct convertir<Objeto, false>
{
	static Objeto serializar (Objeto obj) {
		return obj;
	}
	static Objeto aplicarCambios (const Objeto& objeto, Objeto base) {
		return base.aplicar(objeto);
	}
	static Objeto deserializar (const Objeto& objeto) {
		return objeto;
	}
};

} /* namespace Serializacion */
#endif /* CONVERTIR_H_ */
