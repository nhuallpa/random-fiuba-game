#pragma once

#ifndef _UTIL_H_
#define _UTIL_H_

#include "ParserYaml.h"
#include <stdlib.h>


struct s_point{
	int x;
	int y;
};
typedef struct s_point tPoint;

class Util
{
public:
	Util(void);
	~Util(void);

	/**
	* Convert std::string to int
	* @param number a string int
	* @return int 
	*/
	static int string2int(std::string number);


	/**
	* Get the scale factor in both axis x and y
	* @return std::pair<float,float> a pair of scale factor
	*/
	static std::pair<float,float> getTransformFromU2PX();

	/**
	* Convert std::string to float
	* @param number a string float
	* @return float
	*/
	static float string2float(std::string number);


	/**
	* Convert a coordinate x y to coordinate in SDL system reference
	* @param x Value of axis x in domain
	* @param y Value of axis y in domain
	* @return aPoint in SLD system reference
	*/
	static tPoint convertPointUL2PXSDL(float x, float y);
};



#endif