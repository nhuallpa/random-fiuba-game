
// Descomentar este código para probar SDL
#include <iostream>

#include "./Administrador.h"
#include "./utils/Log.h"

#include <yaml-cpp/yaml.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "utils/ParserYaml.h"
#include "utils/PersistYaml.h"

void persistir(){
	PersistYaml* aPersist=PersistYaml::getInstance();
	PersistYaml* aPersist2=PersistYaml::getInstance();
	aPersist->setNivelNombre("nivel1");
	aPersist->setNivelFondo("fondo.png");
	aPersist->setNivelAlto("999");
	aPersist->setNivelAncho("777");
	aPersist->setElem("circulo","12","46","90");
	aPersist->setElem("triangulo","122","462","902");
	aPersist2->escribirYaml("out.yaml");


}


int main(int argc, char* argv[]) {

	//parsear();
	std::string path = (argc > 1) ? argv[1] : DEFAULT_YAML_LEVEL;
	ParserYaml* aParser = ParserYaml::getInstance(path);

	//std::cout<<"data elementos:\n\t";
	//for(unsigned i=0;i<aParser->getCantDataElem();i++){
	//	std::cout<<"nombre: "<< aParser->getDataElemNombre(i)<<"\n\t";
	//	std::cout<<"imagen: "<< aParser->getDataElemImagen(i)<<"\n\t";
	//}


	//std::cout<<"niveles:\n\t";
	//for(unsigned i=0;i<aParser->getCantNiveles();i++){
	//	std::cout<<"nombre: "<< aParser->getNivelNombre()<<"\n\t";
	//	std::cout<<"fondo: "<< aParser->getNivelFondo()<<"\n\t";
	//	std::cout<<"ancho: "<< aParser->getNivelAncho()<<"\n\t";
	//	std::cout<<"alto: "<< aParser->getNivelAlto()<<"\n\t";
	//	
	//	
	//std::cout<<"elementos:\n\t\t";
	//for(unsigned j=0;j<aParser->getCantElem(i);j++){
	//		std::cout<<"tipo: "<< aParser->getElemNombre(i,j)<<"\n\t\t";
	//		std::cout<<"x: "<< aParser->getElemX(i,j)<<"\n\t\t";
	//		std::cout<<"y: "<< aParser->getElemY(i,j)<<"\n\t\t";
	//		std::cout<<"angulo: "<< aParser->getElemAngulo(i,j)<<"\n\t\t";
	//	}
	//}

	Administrador administrador; 
	administrador.run();

	

	return 0;
}


////Descomentar este código para probar YAML



