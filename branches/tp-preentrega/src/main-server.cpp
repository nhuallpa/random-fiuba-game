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
#include "Servidor\Servidor.h"
#define SERVER_PORT 10025

using namespace std;


int main(int argc, char* argv[]) {
	
	Log::logSide = LOG_SERVER;
	std::string path = (argc > 1) ? argv[1] : DEFAULT_YAML_SERVER;
	ParserYaml* aParser = ParserYaml::getInstance(path);

	Servidor mySrv( SERVER_PORT , Util::string2int(aParser->getMetaMaxPlay()) );
	
	while(true){
		Sleep(200);

		//TODO: Dejar el stepOver thread aca
	}
	return 0;

}



