#pragma once


#include <fstream>
#include <list>
#include <yaml-cpp/yaml.h>
#include <vector>
#include <sstream>
#include "../utils/Constantes/Constantes.h"
#include "./Log.h"
#include <boost/lexical_cast.hpp>
#include <boost/math/special_functions/round.hpp>


class ParserYaml{
private:
	
	static ParserYaml* pInstance;//puntero a la instacia para hacer el singleton
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
		std::string alto;
		std::string ancho;
		std::vector <stElemento> elem;	
	};

	struct dtElemento{
		std::string nombre;
		std::string imagen;
	};

	struct stTodo{
		std::vector <dtElemento> dataE;//contiene la data de un elemento
		std::vector <stNivel> nivel;//lista de niveles
	};
private:
	
	stTodo todo;	
	std::string yamlNodeToString(const YAML::Node&);
	void cargarElementos(const YAML::Node&,std::vector <stElemento>&);
	void cargarDataElementos(const YAML::Node&,std::vector <dtElemento>&);
	void cargarNiveles(const YAML::Node&,std::vector <stNivel>&);
		
	bool existeNivel(std::string,std::vector <stNivel>&);
	bool existeElemen(std::string,std::vector <dtElemento>&);

	void startWithDefaultLevel();
	
	bool esNumero(std::string);
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
	void cargarConfYaml(std::string);
	void cargarNivelYaml(std::string);
	std::string getImElem(const std::vector <dtElemento>,std::string);
	bool getDefault();


	//++++++geters+++++++++
	
	//dataElem
	int getCantDataElem();
	std::string getDataElemNombre(int);//devuelve el nombre de el dataElem de la posicion que se le pase
	std::string getDataElemImagen(int);
	
	
	//todo esto sirve para muchos niveles
	//nivel
	int getCantNiveles();
	std::string getNivelNombre(int);
	std::string getNivelFondo(int);
	std::string getNivelAlto(int);
	std::string getNivelAncho(int);

	//elemento en nivel
		//el primer int que siempre se pasa es para el nivel especificado de la lista de niveles
	int getCantElem(int);
	std::string getElemNombre(int,int);
	std::string getElemX(int,int);
	std::string getElemY(int,int);
	std::string getElemAngulo(int,int);

	
	
	
	//para trabajar con un solo nivel
	std::string getNivelNombre();
	std::string getNivelFondo();
	std::string getNivelAlto();
	std::string getNivelAncho();

	//elemento en nivel
		//el primer int que siempre se pasa es para el nivel especificado de la lista de niveles
	int getCantElem();
	std::string getElemNombre(int);
	std::string getElemX(int);
	std::string getElemY(int);
	std::string getElemAngulo(int);


};