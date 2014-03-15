#include "Rect.h"

#include "Serializacion/Vec2.h"
#include "Serializacion/Interno/Mapa.h"

namespace Serializacion {

Objeto convertir<Rect>::serializar (Rect obj) {
	Mapa retval;
	retval["centro"] = obj.centro();
	retval["tam"] = obj.tam();
	return retval;
}

Rect convertir<Rect>::deserializar (const Objeto& objeto) {
	return aplicarCambios(objeto, Rect());
}

Rect convertir<Rect>::aplicarCambios (const Objeto& objeto, Rect base) {
	Rect retval = base;
	Mapa mapa = objeto.getMapa();
	if (mapa.existe("centro")) {
		retval.setCentro(mapa["centro"]);
	}
	if (mapa.existe("tam")) {
		retval.setTam(mapa["tam"]);
	}
	return retval;
}

} /* namespace Serializacion */
