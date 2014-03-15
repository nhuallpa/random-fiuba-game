#include "Vec2.h"

#include "Serializacion/Interno/Mapa.h"

namespace Serializacion {

Objeto convertir<Vec2>::serializar (Vec2 obj) {
	Mapa retval;
	retval["x"] = obj.x;
	retval["y"] = obj.y;
	return retval;
}

Vec2 convertir<Vec2>::deserializar (const Objeto& objeto) {
	return aplicarCambios(objeto, Vec2());
}

Vec2 convertir<Vec2>::aplicarCambios (const Objeto& objeto, Vec2 base) {
	Vec2 retval = base;
	Mapa mapa = objeto.getMapa();
	mapa.asignar_si(retval.x, "x");
	mapa.asignar_si(retval.y, "y");
	return retval;
}

} /* namespace Serializacion */
