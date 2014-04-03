#ifndef TRANSFORM_H_
#define TRANSFORM_H_

#include "ParserYaml.h"
#include <utility>   

std::pair<float,float> getTransformFromU2PX(){
	ParserYaml* aParser = ParserYaml::getInstance();
	std::pair<float,float> vec;
	float x;
	float y;

	y = aParser->getEscenarioAltoP() / aParser->getEscenarioAltoU();
	x = aParser->getEscenarioAnchoP() / aParser->getEscenarioAnchoU();
	vec = std::make_pair(x,y);

	return vec;
}


#endif