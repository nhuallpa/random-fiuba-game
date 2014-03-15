/*
 * ConvertStr.cpp
 *
 *  Created on: 19/09/2013
 *  Last Amended: 19/09/2013
 *      Author: natuchis
 */

#include "ConvertStr.h"

#include <yaml-cpp/mark.h>
#include <sstream>

ConvertStr::ConvertStr(const YAML::Mark& mark, const std::string& msj) : output() {
	std::stringstream builder;
	builder.str("");
	builder << "Line: " << (mark.line + 1) << " "
	        << "Col: " << (mark.column + 1) << ". "
	        << msj;
	this->output = builder.str();
}

ConvertStr::~ConvertStr() {
}

std::string ConvertStr::getString() {
	return this->output;
}
