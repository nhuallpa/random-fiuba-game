#ifndef SERIALIZACION_RECT_H_
#define SERIALIZACION_RECT_H_

#include "Serializacion/Interno/convertir.h"
#include "Utils/Rect.h"

namespace Serializacion {

template <>
struct convertir<Rect>
{
	static Objeto serializar (Rect obj);
	static Rect deserializar (const Objeto& objeto);
	static Rect aplicarCambios (const Objeto& objeto, Rect base);
};

} /* namespace Serializacion */
#endif /* SERIALIZACION_RECT_H_ */
