#include "archivo.h"

#include "Log/Suceso.h"
#include "Serializacion/Interno/Objeto.h"
#include "Serializacion/YAML/ConvertStr.h"
#include "Serializacion/YAML/Objeto.h"
#include <yaml-cpp/yaml.h>
#include <iostream>
#include <fstream>

Serializacion::Objeto YAML_leerArchivo (std::string path)
{
	try {
		YAML::Node nodo = YAML::LoadFile (path);

		Serializacion::Objeto obj = nodo.as<Serializacion::Objeto>();
		return obj;

	} catch (YAML::ParserException& e) {
		std::cout << e.what() << std::endl;
	} catch (YAML::BadFile& e) {
		std::string output("No se puede cargar el archivo especificado. Se crea Escenario vacio con imagen por defecto.");
		Log::Suceso (Log::ERROR, output);
	} catch (YAML::TypedBadConversion<Serializacion::Objeto>& e) {
		ConvertStr output(e.mark, "No se puede convertir a Escenario.");
		Log::Suceso (Log::ERROR, output.getString());
	}

	return Serializacion::Objeto();
}

void YAML_escribirArchivo (std::string path, Serializacion::Objeto valor)
{
	std::ofstream sal;
	sal.open(path.c_str(), std::ofstream::out | std::ofstream::trunc);

	YAML::Node nodo_out;
	nodo_out = valor;

	sal << nodo_out << std::endl;
	sal.close();

	Log::Suceso (Log::INFO, "Se guardo el escenario.");
}
