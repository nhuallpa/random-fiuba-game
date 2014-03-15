#ifndef MAPA_H_
#define MAPA_H_

#include <map>
#include <string>
#include "Serializacion/Interno/convertir.h"
#include "Serializacion/Interno/Objeto.h"

namespace Serializacion {

class Mapa
{
public:
	Mapa ();
	Mapa (const Mapa&) = default;
	Mapa (Mapa&&) = default;
	Mapa& operator= (const Mapa&) = default;
	Mapa& operator= (Mapa&&) = default;
	~Mapa() = default;

	bool existe (std::string identificador) const;
	Objeto& operator[] (std::string identificador);
	const Objeto& at (std::string identificador) const;
	template <class T> void asignar_si (T& destino, std::string identificador) const;

	// son tales que x.aplicar(x.diferencia(y)) == y
	Mapa diferencia (Mapa) const;
	Mapa aplicar (Mapa) const;

	bool operator== (Mapa) const;

	std::map<std::string, Objeto> atributos;
};


// implementacion de templates

template <class T>
void Mapa::asignar_si (T& destino, std::string identificador) const
{
	if (existe(identificador)) {
		destino = at(identificador).aplicadoA(std::move(destino));
	}
}

} /* namespace Serializacion */
#endif /* MAPA_H_ */
