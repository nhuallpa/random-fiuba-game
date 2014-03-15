#ifndef ENTIDADWRAPPER_H_
#define ENTIDADWRAPPER_H_

#include "Modelo/TipoElemento.h"
#include "Modelo/Jugador.h"
#include "Utils/Vec2.h"
#include <list>
#include <memory>
#include <vector>

namespace Modelo {

enum class TipoAccion : size_t {
	levantarFlippers,
	bajarFlippers,
	clickearFigura
};

class Entidad;
class Mundo;
class MundoBase;

class EntidadWrapper {

public:
	EntidadWrapper();

	EntidadWrapper(const EntidadWrapper&) = default;
	EntidadWrapper(EntidadWrapper&&);
	EntidadWrapper& operator= (EntidadWrapper);
	bool operator== (EntidadWrapper rhs) const;
	bool operator<(EntidadWrapper rhs) const;
	bool operator>(EntidadWrapper rhs) const;
	~EntidadWrapper() = default;

	// La soga y la correa son los unicos que no colisionan con otras entidades.
	bool colicionaCon(EntidadWrapper otraEntidad) const;

	// Aca sigue una serie de checkeos booleanos.
	// De estos, llamar x.m() equivale a llamar Modelo::m(x.clase())
	bool esMovil() const;
	bool esNoMovil() const;
	bool esElementoPuente() const; //1
	bool esSogeable() const; //2
	bool esCorreable() const; //3
	bool esInteractiva() const;
	bool esAtravesable() const;

	// (1) Para soga y correa.
	bool vincular(EntidadWrapper, EntidadWrapper, Vec2 a, Vec2 b);

	// (1) Reconstruye los atributos centro/tamanio/angulo.
	void regenerar();

	// (2) (3) Para entidades sogeables y correables.
	bool tieneElemPuenteAtado() const;

	// (2) (3) Devuelve el punto en donde el objeto se puede unirse a una soga o una correa (segun corresponda).
	// Lista vacia seria que no se puede unirse.
	// No checkea si el objeto ya esta unido a algo.
	std::vector<Vec2> lugarDondeSePuedeUnir() const;

	// (2) (3) Si hay soga o correa unida, elimina la union en la entidad enlazada, y devuelve el elmento puente unido.
	std::list<EntidadWrapper> desenlazarElemPuente();


// Accesores de atributos
	Modelo::TipoElemento& clase();
	Modelo::TipoElemento clase() const;
	Vec2& centro();			// (x, y)
	Vec2 centro() const;
	Vec2& tamanio();		// (ancho, alto)
	Vec2 tamanio() const;
	float& angulo();		// Para plataforma, polea (en grados)
	float angulo() const;
	bool& estadoNormal();	// Para los motores, como tambien el sentido del yunque, tijera
	bool estadoNormal() const;
	bool& accionar(); 	//Para elementos interactivos: bomba, globo, pinball
	bool accionar() const;
	float& distanciaRecorrida ();	// Para cinta	TODO: me da verguenza esto...
	float distanciaRecorrida () const;

	float radio() const;

	// (1) Para soga y correa: objetos atados
	EntidadWrapper entidadExtremoA();
	const EntidadWrapper entidadExtremoA() const;
	EntidadWrapper entidadExtremoB();
	const EntidadWrapper entidadExtremoB() const;
	// (1) Para soga y correa: en qué punto de los objetos esta atado el elemento puente
	Vec2& puntoDeLigaduraEntidadA();
	Vec2 puntoDeLigaduraEntidadA() const;
	Vec2& puntoDeLigaduraEntidadB();
	Vec2 puntoDeLigaduraEntidadB() const;

	// (2) (3) Para entidades sogeables y correables
	std::list<EntidadWrapper> elemPuenteAtado();
	const std::list<EntidadWrapper> elemPuenteAtado() const;

	// Para el juego en red
	TipoJugador& jugador();
	TipoJugador jugador() const;
	size_t id() const;
	bool valido() const;
	void borrar();


private:
	size_t id_; // si es 0, el contenido esta en entidad, si no en mundo[id_]
	std::weak_ptr<MundoBase> mundo;

	friend class Mundo;
	EntidadWrapper(size_t id_, std::weak_ptr<MundoBase> mundo);

public:
	// lanza excepcion si falla
	Entidad* base ();
	const Entidad* base () const;
};


} /* namespace Modelo */

#endif /* ENTIDADWRAPPER_H_ */
