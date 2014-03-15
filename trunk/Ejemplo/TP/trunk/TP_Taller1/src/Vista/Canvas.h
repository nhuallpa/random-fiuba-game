#ifndef CANVAS_H_
#define CANVAS_H_

#include "Contenedor.h"
#include "Modelo/Jugador.h"
#include "Modelo/Mundo.h"
#include "Utils/Rect.h"
#include <map>

class FuentePosicion;
class DestinoDibujo;
class FiguraVista;
class Escenario;

namespace Modelo {
	class Mundo;
	class EntidadWrapper;
	class Jugador;
	class Juego;
}


class Canvas : public Contenedor
{
public:
	Canvas (const FuentePosicion& fuente, Dibujable* destino,
	        Modelo::Juego *juego, const Rect& regionModeloAMostrar);

	Canvas (const Canvas&) = default;
	Canvas (Canvas&&) = default;
	Canvas& operator= (const Canvas&) = default;
	Canvas& operator= (Canvas&&) = default;
	virtual ~Canvas ();

	Vec2 tamUnidadLogica() const;

	virtual LayoutInfo getLayoutInfo();

	virtual vista::ClickInfo recibirClick(Vec2);
	bool aEliminar (Vec2 posicionRespectoPadre);
	virtual bool recibirFigura (const FiguraVista *elemento, Vec2 pos,
			vista::PrioridadDibujo prioridad = vista::PrioridadDibujo::normal);
	virtual bool recibirElementoPuente(FiguraVista *elemento, Vec2 extremoA,
			Vec2 extremoB, vista::PrioridadDibujo prioridad = vista::PrioridadDibujo::normal);
	void setBackground(std::string filename, DestinoDibujo* destino);

	Rect getRegionModelo ();
	size_t getCuenta (Modelo::TipoJugador, Modelo::TipoElemento);

	bool accionarElementos(FiguraVista* figura, Vec2 pos, Modelo::TipoAccion accion);

protected:
	virtual void regenerar();

private:
	Dibujable* destino;
	Modelo::Juego *juego;
	Rect regionModelo;
	std::map<size_t, FiguraVista*> entidadesAgregadas;
	Contenedor *limbo;
	void dibujarRegionDeEdicion(Rect rect);
	void dibujarRegionPropioMasGrueso(Modelo::TipoJugador jugador, Modelo::TipoJugador miJugador, Rect rect);
	bool estaEnMiZona(Modelo::EntidadWrapper entidad);
};

#endif /* CANVAS_H_ */
