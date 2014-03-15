#ifndef MUNDOBASE_H_
#define MUNDOBASE_H_

#include "Modelo/Interno/Entidad.h"
#include <map>
#include <memory>

namespace Modelo {

class MundoBase
{
public:
	MundoBase ();
	MundoBase (const MundoBase&);
	MundoBase (MundoBase&&) = default;
	MundoBase& operator= (MundoBase);
	~MundoBase () = default;

	size_t agregar (std::unique_ptr<Entidad> entidad, bool validarColisiones);
	void quitar (size_t id);

	bool existe (size_t id);
	Entidad* at (size_t id);
	bool colisionan (size_t lhs, size_t rhs);

	std::map<unsigned, std::unique_ptr<Entidad>> contenido;
	size_t ultimoId;
};

} /* namespace Modelo */
#endif /* MUNDOBASE_H_ */
