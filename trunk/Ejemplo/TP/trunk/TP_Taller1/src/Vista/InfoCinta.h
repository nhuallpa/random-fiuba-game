/*
 * InfoCinta.h
 *
 *  Created on: 30/10/2013
 *  Last Amended: 30/10/2013
 *      Author: natuchis
 */

#ifndef INFOCINTA_H_
#define INFOCINTA_H_

#include <map>
#include <vector>
#include <string>

namespace vista {

struct InfoCinta {

	InfoCinta();

	static std::map<int,std::vector<std::string> > imagenes;
};

} /* namespace vista */
#endif /* INFOCINTA_H_ */
