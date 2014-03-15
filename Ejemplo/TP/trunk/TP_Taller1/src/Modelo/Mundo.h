#ifndef MUNDO_H_
#define MUNDO_H_

#include "Modelo/EntidadWrapper.h"
#include "Serializacion/Interno/convertir.h"
#include "Utils/iteracion.h"
#include "Utils/Vec2.h"
#include <map>

namespace Modelo {

class MundoBase;
class Entidad;

class Mundo {

public:
	Mundo();

	Mundo copiaProfunda ();
	Mundo& asignacionProfunda (Mundo);

	Mundo (const Mundo&) = default;
	Mundo (Mundo&&) = default;
	Mundo& operator= (const Mundo&) = default;
	Mundo& operator= (Mundo&&) = default;
	~Mundo() = default;

	EntidadWrapper agregarEntidad (TipoJugador jugador, TipoElemento clase,
			Vec2 centro, Vec2 tamanio, float angulo, bool estadoNormal); // elementos generales
	EntidadWrapper agregarEntidad (TipoJugador jugador, TipoElemento clase,
			EntidadWrapper vinculadoA, EntidadWrapper vinculadoB,
			Vec2 posVinculoA, Vec2 posVinculoB, float alto); // elementos puente
	EntidadWrapper agregarEntidad (Entidad* nuevaEntidad);
	void quitarEntidad(EntidadWrapper unaEntidad);
	void quitarEntidad (size_t id);

	bool colicionaConAlgo(EntidadWrapper unaEntidad);

	typedef std::map<unsigned, std::unique_ptr<Entidad>>::iterator base_iterador;
	typedef std::map<unsigned, std::unique_ptr<Entidad>>::const_iterator base_const_iterador;
	typedef Iterador<EntidadWrapper, base_iterador> iterator;
	typedef Const_Iterador<EntidadWrapper, base_const_iterador> const_iterator;

	iterator begin ();
	iterator end ();
	const_iterator cbegin () const;
	const_iterator cend() const;
	const_iterator begin () const;
	const_iterator end() const;

	EntidadWrapper buscarElemento(unsigned id);
	EntidadWrapper buscarElemento(Vec2 punto);
	bool comprobarUnion(EntidadWrapper lhs, EntidadWrapper rhs, Vec2 a, Vec2 b);
	
	// para confiar en que los cuerpos vienen bien
	bool& validaColisiones ();
	bool validaColisiones () const;

private:
	std::shared_ptr<MundoBase> base;
	bool validaColisiones_;

	iterator construirIterador (base_iterador estadoConstruir);
	const_iterator construirConstIterador (base_const_iterador estadoConstruir) const;

	friend class Serializacion::convertir<Modelo::Mundo>;
};

} /* namespace Modelo */

#endif /* MUNDO_H_ */
