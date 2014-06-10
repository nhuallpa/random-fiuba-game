#include "Util.h"
#include <time.h>
#include <conio.h>

Util::Util(void)
{
}


Util::~Util(void)
{
}

std::map<int, std::pair<float,float> > Util::aimValue;

void Util::iniAimValue(){
	if(!aimValue.size()){
		aimValue.insert(std::pair<int, std::pair<float, float>>( 0, std::pair<float, float>(1,0)));
		aimValue.insert(std::pair<int, std::pair<float, float>>(30, std::pair<float, float>(0.866,0.5)));
		aimValue.insert(std::pair<int, std::pair<float, float>>(45, std::pair<float, float>(0.707,0.707)));
		aimValue.insert(std::pair<int, std::pair<float, float>>(60, std::pair<float, float>(0.5,0.866)));
		aimValue.insert(std::pair<int, std::pair<float, float>>(90, std::pair<float, float>(0,1)));
		aimValue.insert(std::pair<int, std::pair<float, float>>(120, std::pair<float, float>(-0.5,0.866)));
		aimValue.insert(std::pair<int, std::pair<float, float>>(135, std::pair<float, float>(-0.707,0.707)));
		aimValue.insert(std::pair<int, std::pair<float, float>>(150, std::pair<float, float>(-0.866,0.5)));
		aimValue.insert(std::pair<int, std::pair<float, float>>(180, std::pair<float, float>(-1,0)));
		aimValue.insert(std::pair<int, std::pair<float, float>>(210, std::pair<float, float>(-0.866,-0.5)));
		aimValue.insert(std::pair<int, std::pair<float, float>>(225, std::pair<float, float>(-0.707,-0.707)));
		aimValue.insert(std::pair<int, std::pair<float, float>>(240, std::pair<float, float>(-0.5,-0.866)));
		aimValue.insert(std::pair<int, std::pair<float, float>>(270, std::pair<float, float>(0,-1)));
		aimValue.insert(std::pair<int, std::pair<float, float>>(300, std::pair<float, float>(0.5,-0.866)));
		aimValue.insert(std::pair<int, std::pair<float, float>>(315, std::pair<float, float>(0.707,-0.707)));
		aimValue.insert(std::pair<int, std::pair<float, float>>(330, std::pair<float, float>(0.866,-0.5)));
	}

}

/**
*  @DEPRECATED
*/
std::pair<float, float> Util::getTransformFromU2PX(){
	std::pair<float,float> vec;
	/**ParserYaml* aParser = ParserYaml::getInstance();
	float x;
	float y;
	Log::t("Dimensiones Escenario - h:%s ul w:%s ul" , 
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
		Log::t("Factor de escala x: %f px/ul    -     y: %f px/ul",x,y);
	*/
	return vec;
}


tPoint Util::convertPointUL2PXSDL(float x, float y)
{
	tPoint aPoint;
	
	ParserYaml* aParser = ParserYaml::getInstance();
	int heightScreen = atoi(aParser->getEscenarioAltoP().c_str());

	aPoint.x = x * (float)ESCALA_UL2PX;
	aPoint.y = (heightScreen) - (y * (float)ESCALA_UL2PX);	
	

	return aPoint;
}

int Util::string2int(std::string number)
{
	return strtol(number.c_str(), NULL, 10);
}

float Util::string2float(std::string number)
{
	return atof(number.c_str());
}

std::string Util::int2string(int number)
{
	std::stringstream buffer;
	buffer<<number;
	return buffer.str();
}

bool Util::string2bool(std::string sino)
{
	if (sino.compare("si") == 0)
	{
		return true;	
	} 
	else if (sino.compare("si") != 0) 
	{
		return false;
	}
	return false;
}


bool Util::esUnsInt(std::string str) 
{
	for (unsigned int i=0;i<str.length();i++)
		if (isdigit(str[i])==0) return false;
	return true;

}

std::map<std::string, std::string> Util::loadProperteries(std::string str)
{
	std::ifstream configFile(str.c_str(), std::ios::in);
	std::map<std::string, std::string> properties;
	std::string l_property;
	if (configFile.is_open())
	{
		configFile.seekg(std::ios::beg);
		while (!configFile.eof()) 
		{
			std::getline(configFile, l_property);
			int posComentSymbol = l_property.find('#');
			if (posComentSymbol == 0)
			{
				continue;
			}
			int posAssignSymbol = l_property.find('=');
			if (posAssignSymbol > 0)
			{
				std::string key = l_property.substr(0, posAssignSymbol);
				std::string value = l_property.substr(posAssignSymbol+1);
				properties[key] = value;	
			}
		}
		configFile.close();
	}
	return properties;
}


int Util::getRandom(int min, int max){
	static unsigned int i = time(NULL);
	srand(i++);
	return rand() % max + min;
}


std::string Util::actionString(Movement action)
{
	std::string sValue;

	if (action == MOVE_RIGHT)
	{
		sValue.assign("MOVE_RIGHT");
	} 
	else if (action == MOVE_LEFT)
	{
		sValue.assign("MOVE_LEFT");
	}
	else if (action == JUMP)
	{
		sValue.assign("JUMP");
	}
	else if (action == JUMP_LEFT)
	{
		sValue.assign("JUMP_LEFT");
	}
	else if (action == JUMP_RIGHT)
	{
		sValue.assign("JUMP_RIGHT");
	}
	else if (action == INIT_PLACEMENT)
	{
		sValue.assign("INIT_PLACEMENT");
	}
	else if (action == MOVE_STOP)
	{
		sValue.assign("MOVE_STOP");
	}
	else if (action == DEAD)
	{
		sValue.assign("DEAD");
	}
	else if (action == WITH_WEAPON)
	{
		sValue.assign("WITH_WEAPON");
	}
	else if (action == NOT_CONNECTED)
	{
		sValue.assign("NOT_CONNECTED");
	}
	else if (action == NOT_CONNECTED_LEFT)
	{
		sValue.assign("NOT_CONNECTED_LEFT");
	}
	else if (action == NOT_CONNECTED_RIGHT)
	{
		sValue.assign("NOT_CONNECTED_RIGHT");
	}
	else if (action == MOVELESS_LEFT)
	{
		sValue.assign("MOVELESS_LEFT");
	}
	else if (action == MOVELESS_RIGHT)
	{
		sValue.assign("MOVELESS_RIGHT");
	}
	else if (action == MOVELESS)
	{
		sValue.assign("MOVELESS");
	}
	else if (action == EXPLOSION)
	{
		sValue.assign("EXPLOSION");
	}
	else if (action == MISSIL_FLYING)
	{
		sValue.assign("MISSIL_FLYING");
	}
	else if (action == DO_SHOOT)
	{
		sValue.assign("DO_SHOOT");
	} else {
		sValue.assign("");
	}
	return sValue;
}