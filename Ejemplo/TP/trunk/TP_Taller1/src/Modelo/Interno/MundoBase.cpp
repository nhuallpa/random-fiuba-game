#include "MundoBase.h"

#include "Log/Suceso.h"

namespace Modelo {

MundoBase::MundoBase()
	: contenido()
	, ultimoId(0)
{
}

MundoBase::MundoBase (const MundoBase& original)
	: contenido()
	, ultimoId(original.ultimoId)
{
	for (auto& ent : original.contenido) {
		contenido[ent.first] = std::unique_ptr<Entidad>(Entidad::clonar(ent.second.get()));
	}
}

MundoBase::~MundoBase()
{
}

MundoBase& MundoBase::operator= (MundoBase original)
{
	using std::swap;
	swap(contenido, original.contenido);
	swap(ultimoId, original.ultimoId);
	return *this;
}

size_t MundoBase::agregar (std::unique_ptr<Entidad> entidad, bool validarColisiones)
{
	if (validarColisiones) {
		for (auto& par : contenido) {
			if (par.second->colicionaCon(entidad.get())) {
				auto msg = "Se intento agregar una entidad que colisiona con otra.";
				throw Log::Suceso (Log::ERROR, msg);
			}
		}
	}
	if (entidad->id == 0) {
		entidad->id = ultimoId + 1;
		++ultimoId;
	} else {
		ultimoId = std::max(entidad->id, ultimoId);
	}
	size_t id = entidad->id;
	contenido[id] = std::move(entidad);
	return id;
}

void MundoBase::quitar (size_t id)
{
	if (contenido.count(id) == 0) return;

	if (esElementoPuente(contenido[id]->clase)) {
		contenido[contenido[id]->idEntidadExtremoA]->elemPuenteAtado.remove(id);
		contenido[contenido[id]->idEntidadExtremoB]->elemPuenteAtado.remove(id);
	} else {
		auto puentes = contenido[id]->elemPuenteAtado;
		for (size_t idUnion : puentes) {
			quitar(idUnion);
		}
	}
	contenido.erase(id);
}

bool MundoBase::existe (size_t id)
{
	return contenido.count(id) != 0;
}

Entidad* MundoBase::at (size_t id)
{
	if (!existe(id)) {
		return nullptr;
	}
	return contenido[id].get();
}

bool MundoBase::colisionan (size_t lhs_id, size_t rhs_id)
{
	if (lhs_id == rhs_id) {
		return false;
	}
	if (!existe(lhs_id) || !existe(rhs_id)) {
		return false;
	}
	return at(lhs_id)->colicionaCon(at(rhs_id));
}

} /* namespace Modelo */
