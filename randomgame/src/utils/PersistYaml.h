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
		std::string tipo;
		std::string x;
		std::string y;
		std::string alto;
		std::string ancho;
		std::string color;
		std::string estatico;
		std::string masa;
		std::string rot;
	};

	struct stEscenario{
		std::string ancho;
		std::string alto;
		std::string altoP;
		std::string anchoP;
		std::string agua;
		std::string tierra;
		std::string cielo;

		std::vector <stElemento> elem;	
	};

	stElemento elem;
	stEscenario escenario;

	void destroyLevel();


public:
	PersistYaml();
	virtual ~PersistYaml();
	static PersistYaml* getInstance();



	void setEscenarioAnchoU(std::string);
	void setEscenarioAltoU(std::string);
	void setEscenarioAltoP(std::string);
	void setEscenarioAnchoP(std::string);
	void setEscenarioAgua(std::string);
	void setEscenarioTierra(std::string);
	void setEscenarioCielo(std::string);

	void setElemTipo(std::string);
	void setElemX(std::string);
	void setElemY(std::string);
	void setElemRot(std::string);
	void setElemAlto(std::string);
	void setElemAncho(std::string);
	void setElemMasa(std::string);
	void setElemEstatico(std::string);
	void setElemColor(std::string);

	void setEscenarioElem(stElemento);

	void setElem(std::string,std::string,std::string,std::string,std::string,std::string,std::string,std::string,std::string);

	void escribirYaml(std::string);

};