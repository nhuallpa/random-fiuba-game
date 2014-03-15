/*
 * TipoAviso.h
 *
 *  Created on: 04/12/2013
 *  Last Amended: 04/12/2013
 *      Author: natuchis
 */

#ifndef TIPOAVISO_H_
#define TIPOAVISO_H_

#include <cstdint>

namespace  vista {

enum class TipoAviso : uint8_t {
	Mision,
	Win,
	Error,
};

} /* namespace vista */
#endif /* TIPOAVISO_H_ */
