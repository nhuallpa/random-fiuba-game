#include "PersistYaml.h"
#include <vector>
#include <iostream>

PersistYaml::PersistYaml(){}
PersistYaml::~PersistYaml(){}

void PersistYaml::DestroySingleton(){
	if(pInstance != NULL) delete pInstance;
}

PersistYaml* PersistYaml::getInstance(){
	if(pInstance == NULL){
		pInstance = new PersistYaml();
		atexit(&DestroySingleton);
	}
	return pInstance;
}



void PersistYaml::setNivelNombre(std::string nombre){
	this->nivel.nombre = nombre;
}

void PersistYaml::setNivelFondo(std::string fondo){
	this->nivel.fondo = fondo;
}

void PersistYaml::setNivelAncho(std::string ancho){
	this->nivel.ancho = ancho;
}

void PersistYaml::setNivelAlto(std::string alto){
	this->nivel.alto = alto;
}

void PersistYaml::setElemNombre(std::string nombre){
	this->elem.nombre = nombre;
}

void PersistYaml::setElemX(std::string x){
	this->elem.x = x;
}

void PersistYaml::setElemY(std::string y){
	this->elem.y = y;
}

void PersistYaml::setElemAngulo(std::string angulo){
	this->elem.angulo = angulo;
}

void PersistYaml::setNivelElem(stElemento elem){
	this->nivel.elem.push_back(elem);
}

void PersistYaml::setElem(std::string nombre,std::string x,std::string y,std::string angulo){
	stElemento elem;
	elem.nombre = nombre;
	elem.x = x;
	elem.y = y;
	elem.angulo = angulo;
	this->nivel.elem.push_back(elem);
}

void PersistYaml::escribirYaml(std::string fileOut){
	int i;
	YAML::Emitter out;
	out << YAML::BeginMap;
	out << YAML::Key << "niveles";
	out << YAML::Value << YAML::BeginSeq;
	out << YAML::BeginMap;
	out << YAML::Key << "nombre";
	out << YAML::Value << this->nivel.nombre;
	out << YAML::Key << "background";
	out << YAML::Value << this->nivel.fondo;
	out << YAML::Key << "ancho";
	out << YAML::Value << this->nivel.ancho;
	out << YAML::Key << "alto";
	out << YAML::Value << this->nivel.alto;
	out << YAML::Key << "elementos";
	out << YAML::Value << YAML::BeginSeq;
	for(unsigned i=0;i<this->nivel.elem.size();i++){
		stElemento elem = this->nivel.elem[i];
		out << YAML::BeginMap;
		out << YAML::Key << "nombre";
		out << YAML::Value << elem.nombre;
		out << YAML::Key << "x";
		out << YAML::Value << elem.x;
		out << YAML::Key << "y";
		out << YAML::Value << elem.y;
		out << YAML::Key << "angulo";
		out << YAML::Value << elem.angulo;
		out << YAML::EndMap;		
	}
	out << YAML::EndMap;
	out << YAML::EndSeq;
	
	out << YAML::EndSeq;
	
	/* escribe el archivo*/
	std::ofstream file(fileOut.c_str());
	out << YAML::EndMap;
	file << out.c_str()<<std::endl;
	file.close();

	//vacia los maps internos - TODO @Optimizacion: guardar solo lo que cambia
	this->destroyLevel();
}

void PersistYaml::destroyLevel(){
	this->nivel.elem.clear();
}


PersistYaml* PersistYaml::pInstance = NULL;