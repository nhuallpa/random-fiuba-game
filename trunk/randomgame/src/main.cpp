
// Descomentar este código para probar SDL
#include <iostream>

#include "./SystemManager.h"
#include "./utils/Log.h"
#include <Box2D/Box2D.h>
#include <yaml-cpp/yaml.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "utils/ParserYaml.h"
#include "utils/PersistYaml.h"
#include "Servidor\modelo\HandleContour.h"
#include <cstdio>
#include "Servidor\modelo\HandlerBmp\ContourBmp.h"


using namespace std;
using namespace server_model_handle;

//void persistir(){
//	PersistYaml* aPersist=PersistYaml::getInstance();
//	PersistYaml* aPersist2=PersistYaml::getInstance();
//	aPersist->setNivelNombre("nivel1");
//	aPersist->setNivelFondo("fondo.png");
//	aPersist->setNivelAlto("999");
//	aPersist->setNivelAncho("777");
//	aPersist->setElem("circulo","12","46","90");
//	aPersist->setElem("triangulo","122","462","902");
//	aPersist2->escribirYaml("out.yaml");
//
//
//}


int main(int argc, char* argv[]) {
	/*
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


	SystemManager sys; 
	sys.run();
	Log::d("INICIO");

	*/

	FILE* pepe = fopen("C:\\random-fiuba-game\\randomgame\\randomgame\\image\\pepe.txt","w");
	if(!pepe) 
		return 1;
	
	Bmp* aBmpFile = new Bmp("C:\\random-fiuba-game\\randomgame\\randomgame\\image\\test1.bmp");
    ContourBmp* aContourBmp = new ContourBmp(aBmpFile);

    list< list<Position*> *>* cc =aContourBmp->getContour();
	delete aContourBmp;

	vector<b2Vec2> lista;
	HandleContour hc;
	vector<vector<b2Vec2>> result;

	list<Position *>::iterator it = (*cc->begin())->end();
	while(it != (*cc->begin())->begin()){
		--it;
		lista.push_back(b2Vec2((float)(*it)->getX(), (float)(*it)->getY()));
	}


	try{
		result = hc.getPolygonConvex(lista, 0.5, 100);
	}
	catch(exception e){
		lista.clear();
	
	}

	vector<b2Vec2>::iterator jt = (*result.begin()).begin();
	vector<vector<b2Vec2>>::iterator itt;
	char line[100];

	for(itt = result.begin(); itt != result.end(); itt++){
		vector<b2Vec2> vec = (*itt);
		fputs("Primer poligono \n",pepe);
		for(jt = vec.begin(); jt != vec.end(); jt++){
			sprintf(line, "(%2.4f,%2.4f)\n", (*jt).x,(*jt).y);
			fputs(line, pepe);
		}
		fputs("\n\n", pepe);
	}
			



	ContourBmp::deleteListOfListPositions(cc);



	fclose(pepe);
    cout << "Neo: \"I'm in\" " << endl;

	





	/*
		 <----
		 (1,5)(2,5)(3,5)
		 (1,4)     (3,4)
		 (1,3)     (3,3)
	(0,2)(1,2)     (3,2)
	(0,1)		   (3,1)
	(0,0)(1,0)(2,0)(3,0)


		 ---->
	*/
	/*
	lista.push_back(b2Vec2(1,0));
	lista.push_back(b2Vec2(2,0));
	lista.push_back(b2Vec2(3,0));
	lista.push_back(b2Vec2(3,1));
	lista.push_back(b2Vec2(3,2));
	lista.push_back(b2Vec2(3,3));
	lista.push_back(b2Vec2(3,4));
	lista.push_back(b2Vec2(3,5));
	lista.push_back(b2Vec2(2,5));
	lista.push_back(b2Vec2(1,5));
	lista.push_back(b2Vec2(1,4));
	lista.push_back(b2Vec2(1,3));
	lista.push_back(b2Vec2(1,2));
	lista.push_back(b2Vec2(0,2));
	lista.push_back(b2Vec2(0,1));
	lista.push_back(b2Vec2(0,0));
	
	try{
		result = hc.getPolygonConvex(lista, 0.5, 100);
	}
	catch(exception e){
		lista.clear();
	
	}
	


	lista.clear();*/
	/*								<---
							(7,14)				(12,14)
					(5,13)									(15,13)
		(2,12)														(17,12)

	(1,10)																   (18,10)
	
	
(0,7)																			(19,7)


	(1,4)																   (18,4)
	
		(2,2)														(17,2)
					(5,1)									(15,1)
							(7,0)				(12,0)
		--->
	dis: 0.98..
	*/
	/*
	lista.push_back(b2Vec2(7,0));
	lista.push_back(b2Vec2(12,0));
		lista.push_back(b2Vec2(15,1));
	lista.push_back(b2Vec2(17,2));
		lista.push_back(b2Vec2(18,4));
	lista.push_back(b2Vec2(19,7));
		lista.push_back(b2Vec2(18,10));
	lista.push_back(b2Vec2(17,12));
		lista.push_back(b2Vec2(15,13));
	lista.push_back(b2Vec2(12,14));
	lista.push_back(b2Vec2(7,14));
		lista.push_back(b2Vec2(5,13));
	lista.push_back(b2Vec2(2,12));
		lista.push_back(b2Vec2(1,10));
	lista.push_back(b2Vec2(0,7));
		lista.push_back(b2Vec2(1,4));
	lista.push_back(b2Vec2(2,2));
		lista.push_back(b2Vec2(5,1));
	
	try{
		result = hc.getPolygonConvex(lista, 0.5, 100);
	}
	catch(exception e){
		lista.clear();
	
	}*/
	return 0;
}


////Descomentar este código para probar YAML



