#ifndef ARCHIVO_H_
#define ARCHIVO_H_

#include <string>

namespace Serializacion {
	class Objeto;
}

Serializacion::Objeto YAML_leerArchivo (std::string path);
void YAML_escribirArchivo (std::string path, Serializacion::Objeto valor);

#endif /* ARCHIVO_H_ */
