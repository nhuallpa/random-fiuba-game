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

bool checkArgument(int argc, char* argv[]) {
	if (argc!=4) {
		std::cout<<"Uso: cliente.exe userId serverIp serverPort"<<std::endl;
		return false;
	}
	return true;
}
/*
* param 1 userId
* param 2 serverIp
* param 3 serverPort
**/
int main(int argc, char* argv[]) {
	

	if (checkArgument(argc, argv)) {
		std::string userId = argv[1];
		std::string serverIp = argv[2];
		int serverPort = atoi(argv[3]);
		// ya no debo hacer esto
		std::string path = DEFAULT_YAML_LEVEL;
		ParserYaml* aParser = ParserYaml::getInstance(path);

		Cliente* aClient = new Cliente(userId, serverIp.c_str(), serverPort);

		Log::d("INICIO");
		if( aClient->run() == false ){
			Log::e("Error al correr el juego en modo Cliente");
		}
	}
	

	return 0;
}


