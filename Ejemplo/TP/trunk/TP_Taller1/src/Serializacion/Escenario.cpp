#include "Escenario.h"

#include "Serializacion/Mundo.h"
#include "Serializacion/Interno/Mapa.h"

namespace Serializacion {

Objeto convertir<Escenario>::serializar (Escenario obj) {
	Mapa retval;
	retval["pathFondo"] = obj.pathFondo;
	retval["mundo"] = obj.mundo;
	return retval;
}

Escenario convertir<Escenario>::deserializar (const Objeto& objeto) {
	return aplicarCambios(objeto, Escenario());
}

Escenario convertir<Escenario>::aplicarCambios (const Objeto& objeto, Escenario base) {
	Escenario retval;
	Mapa mapa = objeto.getMapa();

	mapa.asignar_si(retval.pathFondo, "pathFondo");
	mapa.asignar_si(retval.mundo, "mundo");

	return retval;
}

} /* namespace Serializacion */
