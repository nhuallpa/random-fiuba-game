#include "Mundo.h"

#include "Modelo/EntidadWrapper.h"
#include "Modelo/Interno/MundoBase.h"
#include "Serializacion/Entidad.h"
#include "Serializacion/Interno/Mapa.h"

namespace Serializacion {

Objeto convertir<Modelo::Mundo>::serializar (Modelo::Mundo obj) {
	Mapa retval;
	retval["validarColisiones"] = obj.validaColisiones_; // como el resto son size_t, no colisiona
	for (auto& valor : obj) {
		auto ent = static_cast<Modelo::EntidadWrapper>(valor);
		retval[std::to_string(ent.id())] = ent.base();
	}
	return retval;
}

Modelo::Mundo convertir<Modelo::Mundo>::deserializar (const Objeto& objeto) {
	return aplicarCambios(objeto, Modelo::Mundo());
}

Modelo::Mundo convertir<Modelo::Mundo>::aplicarCambios (const Objeto& objeto, Modelo::Mundo base) {
	Modelo::Mundo retval(std::move(base));
	Mapa entidades = objeto.getMapa();

	retval.validaColisiones_ = false;

	auto ptr = retval.base;

	for (auto& par : entidades.atributos) {
		if (par.first == "validarColisiones") {
			continue;
		}
		try {
			size_t id = std::stoi(par.first);
			if (par.second == Objeto::Borrado()) {
				ptr->quitar(id);
			} else if (!ptr->existe(id)) {
				Modelo::Entidad *ent = par.second;
				retval.agregarEntidad(ent);
			} else {
				auto& ptrId = ptr->contenido[id];
				ptrId.reset(par.second.aplicar(ptrId.get()));
			}
		} catch (...) {
			Log::Suceso(Log::ERROR, "Entidad invalida. Omitida.");
		}
	}

	if (entidades.existe("validarColisiones")) {
		retval.validaColisiones_ = entidades["validarColisiones"];
	}

	return retval;
}

} /* namespace Serializacion */
