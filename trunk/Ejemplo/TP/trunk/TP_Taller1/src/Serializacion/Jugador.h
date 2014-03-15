#ifndef SERIALIZACION_JUGADOR_H_
#define SERIALIZACION_JUGADOR_H_

#include "Serializacion/Interno/convertir.h"
#include "Modelo/Jugador.h"

namespace Serializacion {

template <>
struct convertir<Modelo::Jugador>
{
	static Objeto serializar (Modelo::Jugador obj);
	static Modelo::Jugador deserializar (const Objeto& objeto);
	static Modelo::Jugador aplicarCambios (const Objeto& objeto, Modelo::Jugador base);
};

} /* namespace Serializacion */
#endif /* SERIALIZACION_JUGADOR_H_ */
