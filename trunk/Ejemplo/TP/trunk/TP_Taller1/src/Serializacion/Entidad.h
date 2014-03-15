#ifndef SERIALIZACION_ENTIDAD_H_
#define SERIALIZACION_ENTIDAD_H_

#include "Serializacion/Interno/convertir.h"
#include "Modelo/Interno/Entidad.h"

namespace Serializacion {

template <>
struct convertir<Modelo::Entidad*>
{
	static Objeto serializar (Modelo::Entidad* obj);
	static Modelo::Entidad* deserializar (const Objeto& objeto);
	static Modelo::Entidad* aplicarCambios (const Objeto& objeto, Modelo::Entidad* base);
};

} /* namespace Serializacion */
#endif /* SERIALIZACION_ENTIDAD_H_ */
