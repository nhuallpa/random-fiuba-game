#ifndef SERIALIZACION_ESCENARIO_H_
#define SERIALIZACION_ESCENARIO_H_

#include "Serializacion/Interno/convertir.h"
#include "Modelo/Escenario.h"

namespace Serializacion {

template <>
struct convertir<Escenario>
{
	static Objeto serializar (Escenario obj);
	static Escenario deserializar (const Objeto& objeto);
	static Escenario aplicarCambios (const Objeto& objeto, Escenario base);
};

} /* namespace Serializacion */
#endif /* SERIALIZACION_ESCENARIO_H_ */
