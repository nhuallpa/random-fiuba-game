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


void PersistYaml::setEscenarioAnchoU(std::string ancho){
	this->escenario.ancho = ancho;
}

void PersistYaml::setEscenarioAltoU(std::string alto){
	this->escenario.alto = alto;
}

void PersistYaml::setEscenarioAltoP(std::string altoP){
	this->escenario.altoP = altoP;
}
void PersistYaml::setEscenarioAnchoP(std::string anchoP){
	this->escenario.anchoP = anchoP;
}
void PersistYaml::setEscenarioAgua(std::string agua){
	this->escenario.agua = agua;
}
void PersistYaml::setEscenarioTierra(std::string tierra){
	this->escenario.tierra = tierra;
}

void PersistYaml::setEscenarioCielo(std::string cielo){
	this->escenario.cielo = cielo;
}

void PersistYaml::setElemTipo(std::string tipo){
	this->elem.tipo = tipo;
}

void PersistYaml::setElemX(std::string x){
	this->elem.x = x;
}

void PersistYaml::setElemY(std::string y){
	this->elem.y = y;
}

void PersistYaml::setElemRot(std::string rot){
	this->elem.rot = rot;
}

void PersistYaml::setElemAlto(std::string alto){
	this->elem.alto = alto;
}
void PersistYaml::setElemAncho(std::string ancho){
	this->elem.ancho = ancho;
}
void PersistYaml::setElemColor(std::string color){
	this->elem.color = color;
}
void PersistYaml::setElemEstatico(std::string estatico){
	this->elem.estatico = estatico;
}
void PersistYaml::setElemMasa(std::string masa){
	this->elem.masa = masa;
}

void PersistYaml::setEscenarioElem(stElemento elem){
	this->escenario.elem.push_back(elem);
}

void PersistYaml::setElem(std::string tipo,std::string x,std::string y,std::string alto,std::string ancho,std::string color, std::string estatico,std::string rot,std::string masa){
	stElemento elem;
	elem.tipo = tipo;
	elem.x = x;
	elem.y = y;
	elem.rot = rot;
	elem.masa = masa;
	elem.alto = alto;
	elem.ancho = ancho;
	elem.color = color;
	elem.estatico = estatico;

	this->escenario.elem.push_back(elem);
}

void PersistYaml::escribirYaml(std::string fileOut){
	int i;
	YAML::Emitter out;
	out << YAML::BeginMap;
	out << YAML::Key << "escenario";
	out << YAML::Value; //<< YAML::BeginSeq;
	out << YAML::BeginMap;
	out << YAML::Key << "ancho-un";
	out << YAML::Value << this->escenario.ancho;
	out << YAML::Key << "alto-un";
	out << YAML::Value << this->escenario.alto;
	out << YAML::Key << "ancho-px";
	out << YAML::Value << this->escenario.anchoP;
	out << YAML::Key << "alto-px";
	out << YAML::Value << this->escenario.altoP;
	out << YAML::Key << "nivel_agua";
	out << YAML::Value << this->escenario.agua;
	out << YAML::Key << "imagen_tierra";
	out << YAML::Value << this->escenario.tierra;
	out << YAML::Key << "imagen_cielo";
	out << YAML::Value << this->escenario.cielo;
	out << YAML::Key << "objetos";
	out << YAML::Value << YAML::BeginSeq;
	for(unsigned i=0;i<this->escenario.elem.size();i++){
		stElemento elem = this->escenario.elem[i];
		out << YAML::BeginMap;
		out << YAML::Key << "tipo";
		out << YAML::Value << elem.tipo;
		out << YAML::Key << "x";
		out << YAML::Value << elem.x;
		out << YAML::Key << "y";
		out << YAML::Value << elem.y;
		out << YAML::Key << "alto";
		out << YAML::Value << elem.alto;
		out << YAML::Key << "ancho";
		out << YAML::Value << elem.ancho;
		out << YAML::Key << "color";
		out << YAML::Value << elem.color;
		out << YAML::Key << "estatico";
		out << YAML::Value << elem.estatico;
		out << YAML::Key << "rot";
		out << YAML::Value << elem.rot;
		out << YAML::Key << "masa";
		out << YAML::Value << elem.masa;
		out << YAML::EndMap;		
	}
	out << YAML::EndMap;
	out << YAML::EndSeq;
	
	//out << YAML::EndSeq;
	
	/* escribe el archivo*/
	std::ofstream file(fileOut.c_str());
	out << YAML::EndMap;
	file << out.c_str()<<std::endl;
	file.close();

	//vacia los maps internos - TODO @Optimizacion: guardar solo lo que cambia
	this->destroyLevel();
}

void PersistYaml::destroyLevel(){
	this->escenario.elem.clear();
}


PersistYaml* PersistYaml::pInstance = NULL;