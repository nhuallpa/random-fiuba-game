#include "Canvas.h"

#include "Utils/make_unique.h"
#include "Log/Suceso.h"
#include "Modelo/Mundo.h"
#include "Modelo/Escenario.h"
#include "Modelo/Jugador.h"
#include "Modelo/Juego.h"
#include "Vista/ClickInfo.h"
#include "Vista/FiguraVista.h"
#include "Vista/LayoutInfo.h"
#include "Vista/FuentesPosicion/FuenteModelo.h"
#include "Vista/FuentesPosicion/FuenteFuncion.h"
#include "Vista/Color.h"

#include "SDL2/SDL_render.h"
#include <iostream>


Canvas::Canvas (const FuentePosicion& fuente, Dibujable* destino,
	        Modelo::Juego *juego, const Rect& regionModelo)
	: Contenedor(fuente, destino)
	, destino(destino)
	, juego(juego)
	, regionModelo(regionModelo)
	, entidadesAgregadas()
	, limbo()
{
	FuenteFuncion fuenteLimbo (
			[this] () -> Rect {
				return Rect(Vec2(0, 0), this->getFuente()->getTamPadre());},
			[this] () -> float {
				return 0;},
			[this] () -> bool {
				return true;},
			[this] () -> Vec2 {
				return this->getFuente()->getTamPadre();});
	limbo = new Contenedor(fuenteLimbo, destino);
	limbo->setBackground(vista::Color(0,0,0,0), destino);
	this->addElemento(limbo);
}

Canvas::~Canvas () {
}

Vec2 Canvas::tamUnidadLogica() const
{
	return getSuperficie().tam() / regionModelo.tam();
}

LayoutInfo Canvas::getLayoutInfo()
{
	return LayoutInfo(Vec2(100, 100), Vec2(100, 100), true, true, true);
}

vista::ClickInfo Canvas::recibirClick(Vec2 pos)
{
	auto retval = Contenedor::recibirClick(pos);
	retval.iniciaClickeo = false;
	retval.esCanvas = true;

//	// deshabilito si no deberia poder afectar
	if (retval.clickeado != nullptr && juego->miJugador != Modelo::TipoJugador::Escenario) {
		auto fuente = dynamic_cast<FuenteModelo*>(retval.clickeado->getFuente());
		if (fuente != nullptr) {
			auto entidad = fuente->getEntidad();
			if (entidad.valido() && entidad.jugador() != juego->miJugador) {
				retval.puedeArrastrar = false;
				retval.puedeRotar = false;
				retval.puedeResizear = false;
				retval.iniciaClickeo = false;
				retval.puedeUnirse = false;
				retval.esCanvas = false;
			}
			//Para poder clickear globos, esCanvas solo se utiliza como flag en accionarElementos.
			bool esMiZona = estaEnMiZona(fuente->getEntidad());
			if (entidad.valido() && esMiZona) {
				retval.esCanvas = true;
			}
			if(entidad.valido() && !esMiZona && juego->miJugador == entidad.jugador()) {
				retval.esCanvas = false;
			}
			//
		}
	}

	return retval;
}

bool Canvas::estaEnMiZona(Modelo::EntidadWrapper entidad) {
	Rect miZona;
	if(!entidad.valido()) {
		return false;
	}
	Rect zonaEntidad = Rect::deCentro(entidad.centro(), entidad.tamanio());
	for (std::pair<Modelo::TipoJugador,Modelo::Jugador> j : juego->jugadores) {
		if(j.first == juego->miJugador)
			miZona = j.second.regionDeEdicion;
	}
	if(zonaEntidad.colisiona(entidad.angulo(), miZona, 0))
		return true;
	return false;
}

bool Canvas::recibirFigura (const FiguraVista *figura, Vec2, vista::PrioridadDibujo prioridad)
{
	FiguraVista *nFigura = new FiguraVista(*figura);

	Rect supFiguraVista = figura->getSuperficie();
	Rect regionVista = this->getSuperficie();
	Rect supFiguraModelo = supFiguraVista.cambioCoordenadas(regionVista, regionModelo);

	Modelo::TipoJugador jugador = juego->miJugador;

	// Checkeo que la entidad nueva este dentro de la region de edicion del jugador
	if (jugador != Modelo::TipoJugador::Escenario) {
		if (!supFiguraModelo.colisiona(juego->jugadores[jugador].regionDeEdicion)) {
			Log::Suceso(Log::ERROR, "Se intento agregar una entidad fuera de la region de edicion permitido.");
			return false;
		}
	}

	try {
		auto nEntidad = juego->escenario.mundo.agregarEntidad(jugador,
				nFigura->getClase(), supFiguraModelo.centro(),
				supFiguraModelo.tam(), nFigura->getFuente()->getAngulo(), nFigura->getFuente()->getEstadoNormal());

		FuentePosicion* nFuente = new FuenteModelo(nEntidad, this);
		nFigura->setFuente(nFuente);

		if (nEntidad.esAtravesable()) {
			this->addElemento(nFigura, vista::PrioridadDibujo::canio);
		} else {
			this->addElemento(nFigura, prioridad);
		}
		entidadesAgregadas[nEntidad.id()] = nFigura;
	} catch (...) {
		return false;
	}

	return true;
}

bool Canvas::recibirElementoPuente(FiguraVista *figura, Vec2 extremoA, Vec2 extremoB, vista::PrioridadDibujo prioridad)
{
	Rect regionVista = this->getSuperficie();

	Vec2 puntoAmodelo = extremoA.cambioCoordenadas(regionVista, regionModelo);
	Vec2 puntoBmodelo = extremoB.cambioCoordenadas(regionVista, regionModelo);

	Modelo::EntidadWrapper e1 = juego->escenario.mundo.buscarElemento(puntoAmodelo);
	Modelo::EntidadWrapper e2 = juego->escenario.mundo.buscarElemento(puntoBmodelo);
	if (e1 == e2) {
		return false;
	}
	if(!juego->escenario.mundo.comprobarUnion(e1,e2,puntoAmodelo,puntoBmodelo)) {
		return false;
	}

	Modelo::TipoJugador jugador = juego->miJugador;

	if (!(jugador == e1.jugador() && e1.jugador() == e2.jugador())) {
		Log::Suceso(Log::ERROR, "Se intento agregar puente entre dos cosas de diferente jugador.");
		return false;
	}

	FiguraVista *nFigura = new FiguraVista(*figura);
	Rect supModelo = nFigura->getSuperficie().cambioCoordenadas(regionVista, regionModelo);
	auto nUnion = juego->escenario.mundo.agregarEntidad(jugador,
			nFigura->getClase(), e1, e2, puntoAmodelo,
			puntoBmodelo, supModelo.tam().y);
	FuentePosicion* nFuente = new FuenteModelo(nUnion, this);
	nFigura->setFuente(nFuente);
	addElemento(nFigura, vista::PrioridadDibujo::soga);
	entidadesAgregadas[nUnion.id()] = nFigura;

	return true;
}

bool Canvas::aEliminar (Vec2 posicionRespectoPadre){
	auto elemento = buscar_base(posicionRespectoPadre);
	if (elemento != nullptr) {
		Vec2 posicion = posicionRespectoPadre - fuente->getSuperficie().origen();
		if (elemento->aEliminar(posicion) && permitirEliminaciones) {
			FuentePosicion *fuente = elemento->getFuente();
			FuenteModelo *fuenteCasteada = dynamic_cast<FuenteModelo*>(fuente);
			juego->escenario.mundo.quitarEntidad(fuenteCasteada->getEntidad());
		}
	}
	return false;
}

bool Canvas::accionarElementos(FiguraVista* figura, Vec2 pos, Modelo::TipoAccion accion){
	if(!juego->simulando) {
		return false;
	}
	if(Modelo::TipoAccion::levantarFlippers == accion || Modelo::TipoAccion::bajarFlippers == accion ) {
		for (Modelo::EntidadWrapper ent : juego->escenario.mundo) {
			if(ent.jugador() != juego->miJugador) continue;
			if(ent.clase() == Modelo::TipoElemento::PaletaFlipper) {
				if (Modelo::TipoAccion::levantarFlippers == accion)
					ent.accionar() = true;
				else
					ent.accionar() = false;
			}
		}
	} else if (Modelo::TipoAccion::clickearFigura == accion) {
		//Solo puedo reventar el globo cuando está pasando sobre mi area
		if (figura != nullptr) {
			FuenteModelo *fuenteCasteada = dynamic_cast<FuenteModelo*>(figura->getFuente());
			fuenteCasteada->getEntidad().estadoNormal() = false;
		}
	}
	return true;

}

void Canvas::regenerar() {
	std::vector<size_t> idEliminadas;
	for (auto& par : entidadesAgregadas) {
		auto fuenteCasteada = dynamic_cast<FuenteModelo*>(par.second->getFuente());
		if (fuenteCasteada == nullptr) continue;

		if (!fuenteCasteada->getEntidad().valido()) {
			idEliminadas.push_back(par.first);
		}
	}
	for (auto id : idEliminadas) {
		quitarElemento(entidadesAgregadas[id]);
		entidadesAgregadas.erase(id);
	}

	for (Modelo::EntidadWrapper entidad : juego->escenario.mundo) {
		if (entidadesAgregadas.count(entidad.id()) != 0) {
			continue;
		}
		FuenteModelo nFuente(entidad, this);
		FiguraVista *nFig = new FiguraVista(entidad.clase(), nFuente, destino);

		if (entidad.esElementoPuente()) {
			this->addElemento(nFig, vista::PrioridadDibujo::soga);
		} else if (entidad.esAtravesable()) {
			this->addElemento(nFig, vista::PrioridadDibujo::canio);
		} else {
			this->addElemento(nFig);
		}
		entidadesAgregadas[entidad.id()] = nFig;
	}

	// Regenero el limbo
	limbo->vaciar();
	for (auto& par : juego->jugadores) {
		Modelo::Jugador& jugador = par.second;
		if (par.first == juego->miJugador) continue;
		if (jugador.estadoMouse != controlador::Mouse::Estado::arrastrando) continue;

		Modelo::TipoElemento tipo = jugador.elementoMouse;
		Rect regionVistaLocal(Vec2(), getFuente()->getSuperficie().tam());
		FuenteFuncion nFuente(
			[&] () -> Rect {
				Rect supRemota(jugador.fuenteMouse->getSuperficie() + jugador.posicionMouse);
				return supRemota.cambioCoordenadas(jugador.canvasAbsoluto, regionVistaLocal);},
			[&] () -> float {
				return jugador.fuenteMouse->getAngulo();},
			[&] () -> bool {
				return jugador.fuenteMouse->getEstadoNormal();},
			[&] () -> Vec2 {
				return regionVistaLocal.tam();});

		FiguraVista *nFig = new FiguraVista(tipo, nFuente, destino);
		limbo->addElemento(nFig, vista::PrioridadDibujo::arrastrando);
	}

	Contenedor::regenerar();

	// Dibujo las regiones de edicion de todos los jugadores
	for (auto& par : juego->jugadores) {
		Rect rect;
		if (par.first == Modelo::TipoJugador::Jugador1) {
			rect = juego->jugadores[par.second.tipoJugador].regionDeEdicion;
			SDL_SetRenderDrawColor(destino->getRenderer(), 255, 0, 0, 255);
			dibujarRegionDeEdicion(rect);
			dibujarRegionPropioMasGrueso(par.first, juego->miJugador, rect);
		}
		else if (par.first == Modelo::TipoJugador::Jugador2) {
			rect = juego->jugadores[par.second.tipoJugador].regionDeEdicion;
			SDL_SetRenderDrawColor(destino->getRenderer(), 0, 0, 255, 255);
			dibujarRegionDeEdicion(rect);
			dibujarRegionPropioMasGrueso(par.first, juego->miJugador, rect);
		}
		else if (par.first == Modelo::TipoJugador::Jugador3) {
			rect = juego->jugadores[par.second.tipoJugador].regionDeEdicion;
			SDL_SetRenderDrawColor(destino->getRenderer(), 0, 255, 0, 255);
			dibujarRegionDeEdicion(rect);
			dibujarRegionPropioMasGrueso(par.first, juego->miJugador, rect);
		}
		else if (par.first == Modelo::TipoJugador::Jugador4) {
			rect = juego->jugadores[par.second.tipoJugador].regionDeEdicion;
			SDL_SetRenderDrawColor(destino->getRenderer(), 255, 255, 0, 255);
			dibujarRegionDeEdicion(rect);
			dibujarRegionPropioMasGrueso(par.first, juego->miJugador, rect);
		}
	}
}

void Canvas::dibujarRegionPropioMasGrueso(Modelo::TipoJugador jugador, Modelo::TipoJugador miJugador, Rect rect) {
	Vec2 delta(0.02, 0.02);

	// TODO: Forma trucha de un rectangulo con lineas gruesas, no se como se hace correctamente
	if (jugador == miJugador) {
		rect = Rect( rect.origen()-delta, rect.tam()+delta*2 );
		dibujarRegionDeEdicion(rect);
		rect = Rect( rect.origen()-delta/2, rect.tam()+delta );
		dibujarRegionDeEdicion(rect);
		rect = Rect( rect.origen()-delta/3, rect.tam()+delta*2/3 );
		dibujarRegionDeEdicion(rect);
	}
}

void Canvas::dibujarRegionDeEdicion(Rect rect) {
	Rect rectAux = rect.cambioCoordenadas(regionModelo,	Rect(Vec2(), this->getSuperficie().tam()));
	SDL_Rect rectSDL = rectAux.aSDL_Rect();
	SDL_RenderDrawRect(destino->getRenderer(), &rectSDL);
//	SDL_SetRenderTarget(destino->getRenderer(), apariencia.getTexture());
}

void Canvas::setBackground(std::string filename, DestinoDibujo* destino){
	Contenedor::setBackground(filename, destino);
	juego->escenario.pathFondo = filename;
}

Rect Canvas::getRegionModelo () {
	return regionModelo;
}

size_t Canvas::getCuenta (Modelo::TipoJugador jugador, Modelo::TipoElemento clase) {
	size_t cuenta = 0;
	for (auto par : entidadesAgregadas) {
		if (par.second->getClase() != clase) continue;

		auto fuente = dynamic_cast<FuenteModelo*>(par.second->getFuente());
		if (fuente == nullptr) continue;

		if (fuente->getEntidad().jugador() == jugador) {
			cuenta += 1;
		}
	}
	return cuenta;
}
