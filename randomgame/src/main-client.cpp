#include <iostream>
#include "./utils/Log.h"
#include <yaml-cpp/yaml.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "utils/ParserYaml.h"
#include "utils/PersistYaml.h"
#include <cstdio>
#include "Cliente\Cliente.h"


using namespace std;


int main(int argc, char* argv[]) {
	

	std::string path = (argc > 1) ? argv[1] : DEFAULT_YAML_LEVEL;
	ParserYaml* aParser = ParserYaml::getInstance(path);

	Cliente* aClient = new Cliente("Player 1","localhost",10025);

	if( aClient->run() == false ){
		//std::cout << "error" << std::endl;
		Log::e("Error al correr el juego en modo Cliente");
	}


	Log::d("INICIO");

	return 0;
}


////Descomentar este código para probar YAML



