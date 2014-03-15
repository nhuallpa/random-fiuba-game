#ifndef SERIALIZACION_VEC2_H_
#define SERIALIZACION_VEC2_H_

#include "Serializacion/Interno/convertir.h"
#include "Utils/Vec2.h"

namespace Serializacion {

template <>
struct convertir<Vec2>
{
	static Objeto serializar (Vec2 obj);
	static Vec2 deserializar (const Objeto& objeto);
	static Vec2 aplicarCambios (const Objeto& objeto, Vec2 base);
};

} /* namespace Serializacion */
#endif /* SERIALIZACION_VEC2_H_ */
