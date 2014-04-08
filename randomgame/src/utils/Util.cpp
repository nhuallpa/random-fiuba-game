#include "Util.h"


Util::Util(void)
{
}


Util::~Util(void)
{
}


std::pair<float, float> Util::getTransformFromU2PX(){
	ParserYaml* aParser = ParserYaml::getInstance();
	std::pair<float,float> vec;
	float x;
	float y;
	Log::t("Dimensiones Escenario - h:%s  w:%s", 
						aParser->getEscenarioAltoU().c_str() , 
						aParser->getEscenarioAnchoU().c_str());

	Log::t("Dimensiones Pantalla - h:%s px  w:%s px", 
						aParser->getEscenarioAltoP().c_str() , 
						aParser->getEscenarioAnchoP().c_str());

	y = Util::string2float(aParser->getEscenarioAltoP().c_str()) 
						/ Util::string2float(aParser->getEscenarioAltoU().c_str());
	x = Util::string2float(aParser->getEscenarioAnchoP())
						/ Util::string2float(aParser->getEscenarioAnchoU());
	vec = std::make_pair(x,y);

	return vec;
}


int Util::string2int(std::string number)
{
	return strtol(number.c_str(), NULL, 10);
}

float Util::string2float(std::string number)
{
	return atof(number.c_str());
}