#ifndef OBJETO_H_
#define OBJETO_H_

#include <memory>
#include <cstdint>
#include <vector>

namespace Serializacion {

class Hoja;
class Mapa;
class Vector;

class Objeto
{
public:
	Objeto ();
	static Objeto Borrado ();

	Objeto (const Objeto&) = default;
	Objeto (Objeto&&) = default;
	Objeto& operator= (const Objeto&) = default;
	Objeto& operator= (Objeto&&) = default;
	~Objeto () = default;

	template <class T> Objeto (T&& valor);
	template <class T> operator T () const;
	template <class T> T aplicadoA (T&& base) const;

	Objeto (Hoja hoja);
	Objeto (Mapa mapa);
	Objeto (Vector vector);

	Hoja getHoja () const;
	Mapa getMapa () const;
	Vector getVector () const;

	enum struct Tipo {
		Nulo,
		Borrado,
		Hoja,
		Mapa,
		Vector,
	};
	Tipo tipo () const;
	bool casteable (Tipo) const;

	std::vector<uint8_t> aRed () const;
	static Objeto deRed (std::vector<uint8_t> valores);
	static Objeto deRed (std::vector<uint8_t> valores, unsigned& inicio);
	std::string to_string() const;

	// son tales que x.aplicar(x.diferencia(y)) == y
	Objeto diferencia (Objeto) const;
	Objeto aplicar (Objeto) const;

	bool operator== (Objeto) const;
	bool operator!= (Objeto) const;

private:
	Tipo tipo_;
	std::shared_ptr<void> dato; //puntero con el tipo_ correcto
};

} /* namespace Serializacion */

#include "Serializacion/Interno/convertir.h"

namespace Serializacion {

template <class T>
Objeto::Objeto (T&& valor)
	: tipo_(Tipo::Nulo)
	, dato(nullptr)
{
	typedef typename std::decay<T>::type TipoBase;
	if (std::is_same<TipoBase, Objeto>::value || std::is_same<TipoBase, Objeto const>::value) {
		*this = std::forward<T>(valor);
	} else {
		*this = convertir<TipoBase>::serializar(std::forward<T>(valor));
	}
}

template <class T>
Objeto::operator T () const
{
	return convertir<T>::deserializar(*this);
}

template <class T>
T Objeto::aplicadoA (T&& base) const
{
	typedef typename std::decay<T>::type TipoBase;
	if (std::is_same<TipoBase, Objeto>::value || std::is_same<TipoBase, Objeto const>::value) {
		return std::forward<T>(base);
	} else {
		return convertir<TipoBase>::aplicarCambios(*this, std::forward<T>(base));
	}
}

} /* namespace Serializacion */
#endif /* OBJETO_H_ */
