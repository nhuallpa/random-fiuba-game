#ifndef RED_BASE_H_
#define RED_BASE_H_

#include "Red/TipoMensaje.h"
#include <vector>

namespace Red {

bool enviar (int fd, Red::TipoMensaje tipo, std::vector<uint8_t> datos);
bool recibir (int fd, Red::TipoMensaje &tipo, std::vector<uint8_t> &datos);

} /* namespace Red */
#endif /* RED_BASE_H_ */
