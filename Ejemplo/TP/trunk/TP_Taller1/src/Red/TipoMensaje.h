/*
 * TipoMensaje.h
 *
 *  Created on: 14/11/2013
 *  Last Amended: 14/11/2013
 *      Author: natuchis
 */

#ifndef TIPOMENSAJE_H_
#define TIPOMENSAJE_H_

#include <cstdint>

namespace  Red {

enum class TipoMensaje : uint8_t {
	Objeto,
	Jugador,
	Rechazo,
	Vivo,
};

} /* namespace Red */
#endif /* TIPOMENSAJE_H_ */
