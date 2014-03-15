/*
 * Cabecera.h
 *
 *  Created on: 14/11/2013
 *  Last Amended: 14/11/2013
 *      Author: natuchis
 */

#ifndef CABECERA_H_
#define CABECERA_H_

#include "TipoMensaje.h"
#include <cstddef>
#include <vector>

namespace Red {

struct Cabecera {
	Red::TipoMensaje idMensaje;
	uint32_t longitud;

	Cabecera();
	Cabecera(Red::TipoMensaje idMensaje, uint32_t longitud);

	std::vector<uint8_t> aVector() const;
	Cabecera(std::vector<uint8_t>);
	static size_t tamVector ();
};

} /* namespace Red */
#endif /* CABECERA_H_ */
