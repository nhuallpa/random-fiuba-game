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


using namespace std;


int main(int argc, char* argv[]) {
	
	Log::logSide = LOG_SERVER;
	std::string path = (argc > 1) ? argv[1] : DEFAULT_YAML_LEVEL;
	ParserYaml* aParser = ParserYaml::getInstance(path);

	Servidor mySrv(10025,3);
	
	while(true){
		Sleep(200);
	}
	return 0;

}



