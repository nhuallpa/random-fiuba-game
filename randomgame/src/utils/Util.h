#pragma once

#ifndef _UTIL_H_
#define _UTIL_H_

#include "ParserYaml.h"
#include <map>
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
	* Valid int
	* @param number a string int
	* @return true if str has a integer. 
	*/
	static bool esUnsInt(std::string str);

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
	* Convert std::string witch value could be "no" or "si" to bool type
	* @param  a string value "si" or "no"
	* @return true if sino has a "si"
	*/
	static bool string2bool(std::string sino);


	/**
	* Convert std::string witch value could be "no" or "si" to bool type
	* @param  a string value "si" or "no"
	* @return true if sino has a "si"
	*/
	static std::string int2string(int number);
	


	/**
	* Convert a coordinate x y to coordinate in SDL system reference
	* @param x Value of axis x in domain
	* @param y Value of axis y in domain
	* @return aPoint in SLD system reference
	*/
	static tPoint convertPointUL2PXSDL(float x, float y);



	/**
	* Property loader
	* @param file
	* @return map that contains the properties retrived from file
	*/
	static std::map<std::string, std::string> Util::loadProperteries(std::string str);



	static int getRandom(int min, int max);
};



#endif