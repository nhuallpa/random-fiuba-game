/*
 * ConvertStr.h
 *
 *  Created on: 19/09/2013
 *  Last Amended: 19/09/2013
 *      Author: natuchis
 */

#ifndef CONVERTSTR_H_
#define CONVERTSTR_H_

#include <string>

namespace YAML {
	class Mark;
}

class ConvertStr {
public:
	ConvertStr(const YAML::Mark& mark, const std::string& msj);
	virtual ~ConvertStr();

	std::string getString();

private:
	std::string output;
};

#endif /* CONVERTSTR_H_ */
