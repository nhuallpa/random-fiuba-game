#pragma once

#include <fstream>
#include <list>
#include <yaml-cpp/yaml.h>
#include <vector>


class PersistYaml{
public:
	//YAML::Emitter out;
	std::string fileOut;

private:
	//std::string fileOut;
	//YAML::Emitter out;
	static PersistYaml* pInstance;//puntero a la instacia para hacer el singleton
	static void DestroySingleton();



	struct stElemento{
		std::string nombre;
		std::string x;
		std::string y;
		std::string angulo;
	};

	struct stNivel{
		std::string nombre;
		std::string fondo;
		std::string ancho;
		std::string alto;
		std::string altoP;
		std::string anchoP;
		std::string agua;
		std::string tierra;
		std::vector <stElemento> elem;	
	};

	stElemento elem;
	stNivel nivel;

	void destroyLevel();


public:
	PersistYaml();
	virtual ~PersistYaml();
	static PersistYaml* getInstance();



	void setNivelNombre(std::string);
	void setNivelFondo(std::string);
	void setNivelAncho(std::string);
	void setNivelAlto(std::string);
	void setNivelAltoPantalla(std::string);
	void setNivelAnchoPantalla(std::string);
	void setNivelAgua(std::string);
	void setNivelTierra(std::string);

	void setElemNombre(std::string);
	void setElemX(std::string);
	void setElemY(std::string);
	void setElemAngulo(std::string);

	void setNivelElem(stElemento);

	void setElem(std::string,std::string,std::string,std::string);

	void escribirYaml(std::string);

};