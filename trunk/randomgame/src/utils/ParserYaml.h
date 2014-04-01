#pragma once


#include <fstream>
#include <list>
#include <yaml-cpp/yaml.h>
#include <vector>
#include <sstream>
#include "../utils/Constantes/Constantes.h"
#include "./Log.h"
//#include <boost/lexical_cast.hpp>
//#include <boost/math/special_functions/round.hpp>


class ParserYaml{
private:
	
	static ParserYaml* pInstance;//puntero a la instacia para hacer el singleton
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
		std::string alto;
		std::string ancho;
		std::string agua;
		std::string anchoP;
		std::string altoP;
		std::string tierra;
		std::string cielo;
		std::vector <stElemento> elem;	
	};
	/*
	struct dtElemento{
		std::string nombre;
		std::string imagen;
	};*/


	struct stTodo{
		//std::vector <dtElemento> dataE;//contiene la data de un elemento
		stEscenario escenario;
	};
private:
	
	stTodo todo;
	std::string yamlNodeToString(const YAML::Node&);
	void cargarElementos(const YAML::Node&,std::vector <stElemento>&);
//	void cargarDataElementos(const YAML::Node&,std::vector <dtElemento>&);
	void cargarNiveles(const YAML::Node&,stEscenario&);
		
//	bool existeElemen(std::string,std::vector <dtElemento>&);

	void startWithDefaultLevel();
	
	bool esNumero(std::string);
	bool esHexa(std::string);

	bool isDefault;

	std::string confFilePath;
	std::string levelFilePath;

	void initializeElementMap();
	std::map< std::string, std::pair<int,std::string> > elementMap;

	ParserYaml(std::string config, std::string level);
	ParserYaml(std::string config);
	std::string validaAngulo(std::string ang);
	std::string validaPosicion(std::string ang);
	std::string validaPantalla(std::string tam);


public:
	
	

	int getElementPosition(std::string name);
	std::string getImagePath(std::string name);
	std::string getElementType(int id);
	std::string getLevelFilePath();

	ParserYaml();
	virtual ~ParserYaml();
	static ParserYaml* getInstance();
	static ParserYaml* getInstance(std::string file);
	//void cargarConfYaml(std::string);
	void cargarNivelYaml(std::string);
	//std::string getImElem(const std::vector <dtElemento>,std::string);
	bool getDefault();


	//++++++geters+++++++++
	
	//dataElem
	/*int getCantDataElem();
	std::string getDataElemNombre(int);//devuelve el nombre de el dataElem de la posicion que se le pase
	std::string getDataElemImagen(int);*/
	
	
	
	
	//para trabajar con un solo escenario
	std::string getEscenarioAltoU();
	std::string getEscenarioAnchoU();
	std::string getEscenarioAgua();
	std::string getEscenarioTierra();
	std::string getEscenarioAnchoP();
	std::string getEscenarioAltoP();
	std::string getEscenarioCielo();

	//elemento en escenario
		//el primer int que siempre se pasa es para el nivel especificado de la lista de niveles
	int getCantElem();
	std::string getElemTipo(int);
	std::string getElemX(int);
	std::string getElemY(int);
	std::string getElemAncho(int);
	std::string getElemAlto(int);
	std::string getElemColor(int);
	std::string getElemMasa(int);
	std::string getElemEstatico(int);
	std::string getElemRot(int);


};
