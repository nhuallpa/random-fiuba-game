#ifndef ENTIDAD_H_
#define ENTIDAD_H_

#include "Utils/Vec2.h"
#include "Utils/Rect.h"
#include "Modelo/TipoElemento.h"
#include "Modelo/TipoJugador.h"
#include <string>
#include <map>
#include <memory>
#include <vector>

// Es un porcentaje que permite que se toquen un poco los objetos
// se usa en colisiona con
#ifndef PORCENTAJE_PERMITIDO_COLISION
#define PORCENTAJE_PERMITIDO_COLISION 30
#endif

namespace Modelo {

class Jugador;
enum class TipoJugador : size_t;

// Clase padre de la jerarqua que modela a cualquier objeto que puede existir en el juego.
// Maneja unicamente estado local de cada objeto, no observa otras entidades.
struct Entidad
{
	Entidad();
	Entidad(TipoJugador jugador, TipoElemento clase, Vec2 centro = Vec2(0, 0),
	        Vec2 tamanio = Vec2(0, 0), float angulo = 0.0f, bool estadoNormal = true, unsigned int id = 0);
	static Entidad* maker(TipoJugador jugador, TipoElemento clase, Vec2 centro, Vec2 tamanio,
	                      float angulo, bool estadoNormal, unsigned int id);

	Entidad (const Entidad&) = default;
	Entidad (Entidad&&) = default;
	Entidad& operator= (const Entidad&) = default;
	Entidad& operator= (Entidad&&) = default;
	static Entidad* clonar(Entidad *base);
	virtual ~Entidad();

	// La soga y la correa son los unicos que no colisionan con otras entidades.
	virtual bool colicionaCon(Entidad* otraEntidad) const;

	// (1) Reconstruye los atributos centro/tamanio/angulo.
	void regenerar ();

	// (2) (3) Para entidades sogeables y correables.
	virtual bool tieneElemPuenteAtado() const;

	// (2) (3) Devuelve el punto en donde el objeto se puede unirse a una soga o una correa (segun corresponda).
	// Devuelve lista vacia si no se puede unirse.
	// No es afectado si la entidad ya esta unido a algo.
	std::vector<Vec2> puntoLigadura() const;
	std::pair<bool, Vec2> lugarUnionMasCercano(Vec2 pos) const;


// Atributos (todos publicos)
	size_t id;                // "id == 0" significa "id null"  ó  "id no asignado todavia"

	Modelo::TipoElemento clase;
	Vec2 centro;                    // (x, y)
	Vec2 tamanio;                   // (ancho, alto)
	float angulo;                   // Para plataforma, polea (en grados)
	bool estadoNormal;            // Para los motores, como tambien el sentido del yunque, tijera
	float distanciaRecorrida;       // Para animar la cinta, HOY Y SOLO HOY
	// (1) Para soga y correa: objetos atados.
	size_t idEntidadExtremoA;
	size_t idEntidadExtremoB;
	// (1) Para soga y correa: en qué punto de los objetos esta atado el elemento puente.
	// TODO: pasar a offset en puntoLigadura()
	Vec2 puntoDeLigaduraEntidadA;
	Vec2 puntoDeLigaduraEntidadB;

	//Para entidades interactivas
	bool accionar;

	// (2) (3) Para entidades sogeables y correables.
	std::list<size_t> elemPuenteAtado;

	// Para el juego en red
	TipoJugador jugador;


protected:
	// Dado en sistema centro==(0,0), angulo==0
	virtual std::vector<Vec2> puntoLigaduraLocal() const;
};


} /* namespace Modelo */

#endif /* ENTIDAD_H_ */
