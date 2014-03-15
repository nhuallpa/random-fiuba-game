#ifndef SERIALIZACION_JUEGO_H_
#define SERIALIZACION_JUEGO_H_

#include "Serializacion/Interno/convertir.h"
#include "Modelo/Juego.h"

namespace Serializacion {

template <>
struct convertir<Modelo::Juego>
{
	static Objeto serializar (Modelo::Juego obj);
	static Modelo::Juego deserializar (const Objeto& objeto);
	static Modelo::Juego aplicarCambios (const Objeto& objeto, Modelo::Juego base);
};

} /* namespace Serializacion */
#endif /* SERIALIZACION_JUEGO_H_ */
