#ifndef SERIALIZACION_MUNDO_H_
#define SERIALIZACION_MUNDO_H_

#include "Serializacion/Interno/convertir.h"
#include "Modelo/Mundo.h"

namespace Serializacion {

template <>
struct convertir<Modelo::Mundo>
{
	static Objeto serializar (Modelo::Mundo obj);
	static Modelo::Mundo deserializar (const Objeto& objeto);
	static Modelo::Mundo aplicarCambios (const Objeto& objeto, Modelo::Mundo base);
};

} /* namespace Serializacion */
#endif /* SERIALIZACION_MUNDO_H_ */
