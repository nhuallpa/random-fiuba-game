#ifndef SERIALIZACION_OBJETO_H_
#define SERIALIZACION_OBJETO_H_

#include "Serializacion/Interno/Objeto.h"
#include <yaml-cpp/node/convert.h>

namespace YAML {
template<>
struct convert<Serializacion::Objeto> {
	static Node encode(const Serializacion::Objeto& rhs);
	static bool decode(const Node& node, Serializacion::Objeto& rhs);
};
}

#endif /* SERIALIZACION_OBJETO_H_ */
