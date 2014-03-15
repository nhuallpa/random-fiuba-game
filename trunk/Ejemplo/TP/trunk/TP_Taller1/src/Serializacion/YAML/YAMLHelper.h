#ifndef YAMLHELPER_H_
#define YAMLHELPER_H_

#include "Log/Suceso.h"
#include "Serializacion/YAML/ConvertStr.h"
#include <yaml-cpp/yaml.h>

// forwards

template <class RETORNO>
RETORNO YAML_leerFatal (const YAML::Node &nodo, const std::string nombreAtributo,
                        const RETORNO& retornoDefault = RETORNO());

template <class RETORNO>
RETORNO YAML_leer (const YAML::Node &nodo, const std::string nombreAtributo,
                        const RETORNO& retornoDefault = RETORNO());

// implementacion de templates

template <class RETORNO>
RETORNO YAML_leerBase (const YAML::Node &nodo, const std::string nombreAtributo,
                       bool fatal, const RETORNO& retornoDefault)
{
	RETORNO retval(retornoDefault);

	if (!nodo.IsDefined()) {
		std::string mensaje = std::string()
		                    + "No existe el atributo '"
		                    + nombreAtributo
		                    + "'. ";
		ConvertStr output(nodo.mark(), mensaje);
		if (fatal) {
			throw Log::Suceso (Log::ERROR, output.getString());
		} else {
			mensaje += "Usando valor por defecto";
			Log::Suceso (Log::ERROR, output.getString());
		}
	} else if (nodo.IsNull() || (nodo.IsScalar() && nodo.Scalar() == "~")) {
		// sigue hasta retornar default
	} else {
		try {
			retval = nodo.as<RETORNO>();
		} catch (YAML::TypedBadConversion<RETORNO>& e) {
			std::string mensaje = std::string()
		                            + "El atributo '"
		                            + nombreAtributo
		                            + "' no se puede convertir. ";
			ConvertStr output(nodo.mark(), mensaje);
			if (fatal) {
				throw Log::Suceso (Log::ERROR, output.getString());
			} else {
				mensaje += "Usando valor por defecto";
				Log::Suceso (Log::ERROR, output.getString());
			}
		}
	}

	return retval;
}

template <class RETORNO>
RETORNO YAML_leerFatal (const YAML::Node &nodo, const std::string nombreAtributo,
                        const RETORNO& retornoDefault = RETORNO())
{
	return YAML_leerBase<RETORNO>(nodo, nombreAtributo, true, retornoDefault);
}

template <class RETORNO>
RETORNO YAML_leer (const YAML::Node &nodo, const std::string nombreAtributo,
                        const RETORNO& retornoDefault = RETORNO())
{
	return YAML_leerBase<RETORNO>(nodo, nombreAtributo, false, retornoDefault);
}

#endif /* YAMLHELPER_H_ */
