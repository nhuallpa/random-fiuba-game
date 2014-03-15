/*
 * Figura.cpp
 *
 *  Created on: Sep 5, 2013
 *      Author: lucia
 */

#include "FiguraVista.h"

#include "ClickInfo.h"
#include "Imagen.h"
#include "LayoutInfo.h"
#include "FuentesPosicion/FuentePosicion.h"
#include "FuentesPosicion/FuenteModelo.h"
#include "FuentesPosicion/FuenteFuncion.h"
#include "Vista/InfoFiguras.h"
#include "Vista/InfoCinta.h"
#include "Log/Suceso.h"
#include "Utils/Rect.h"
#include "Modelo/Constantes.h"
#include "Modelo/EntidadWrapper.h"
#include <cmath>
#include <vector>

FiguraVista::FiguraVista ()
	: vista::Elemento()
	, pathImagen()
	, imagen()
	, clase()
	, estadoAnimacion(0)
	, contadorAnimacion(99)
{
}

FiguraVista::FiguraVista (Modelo::TipoElemento tipo, const FuentePosicion& fuente,
	                  Dibujable *destino)
	: vista::Elemento(fuente)
	, pathImagen(vista::InfoFiguras::datos[tipo].pathImagenCanvas)
	, imagen(pathImagen, destino)
	, clase(tipo)
	, estadoAnimacion(0)
	, contadorAnimacion(99)
{
}

FiguraVista::~FiguraVista() {
}

void FiguraVista::dibujarse(DestinoDibujo* window) {
	verificarImagen();
	imagen.dibujar(*window, *fuente);
}

void FiguraVista::setSuperfice(const Rect& val){
	this->fuente->setSuperficie(val);
}

LayoutInfo FiguraVista::getLayoutInfo(){
	return LayoutInfo(imagen.tamDibujo());
}

bool FiguraVista::contiene(Vec2 punto) {
	Vec2 puntoParalelo = punto - fuente->getSuperficie().origen() - fuente->getSuperficie().tam() / 2;

	Vec2 puntoRotado = puntoParalelo.rotar(fuente->getAngulo());

	Rect sistemaLocal = Rect::deCentro(Vec2(), fuente->getSuperficie().tam());
	Rect sistemaImagen(Vec2(), imagen.tamDibujo());
	Vec2 puntoImagen = puntoRotado.cambioCoordenadas(sistemaLocal, sistemaImagen);
	return !imagen.esTransparente(puntoImagen);
}

vista::ClickInfo FiguraVista::recibirClick(Vec2 pos) {
	vista::ClickInfo retval(this, pos);

	retval.puedeArrastrar = !Modelo::esElementoPuente(clase);

	if (clase == Modelo::TipoElemento::Plataforma ||
			 clase == Modelo::TipoElemento::Clavo ||
			 clase == Modelo::TipoElemento::Canio ||
			 clase == Modelo::TipoElemento::Codo  ||
			 clase == Modelo::TipoElemento::Clavo ||
			 clase == Modelo::TipoElemento::Carrito ||
			 clase == Modelo::TipoElemento::Vela) {
		retval.puedeRotar = true;
	} else {
		retval.puedeRotar = false;
	}

	if (clase == Modelo::TipoElemento::Plataforma || clase == Modelo::TipoElemento::CintaTransportadora) {
		retval.puedeResizear = true;
	} else {
		retval.puedeResizear = false;
	}

	retval.iniciaClickeo = Modelo::esElementoPuente(clase);
	retval.puedeUnirse = Modelo::esSogeable(clase) || Modelo::esCorreable(clase);

	return retval;
}

void FiguraVista::mover(Vec2 incremento) {
	fuente->setSuperficie(fuente->getSuperficie() + incremento);
}

void FiguraVista::rotar(Vec2 respectoA) {
	//Calculo el angulo de rotacion
	this->fuente->setAngulo(this->getAnguloRotacion(respectoA));
}

bool FiguraVista::aEliminar (Vec2) {
	return true;
}

void FiguraVista::resizear(Vec2 respectoA) {
	Rect sup(fuente->getSuperficie());
	sup.setTam(sup.tam() + Vec2(1,0) * respectoA.rotar(fuente->getAngulo()));
	this->fuente->setSuperficie(sup);
}

void FiguraVista::cambiarForma() {
	switch(clase) {
		case Modelo::TipoElemento::Engranaje:
			this->ciclarEntreRadios();
			break;
		case Modelo::TipoElemento::Motor:
		case Modelo::TipoElemento::MotorRaton:
		case Modelo::TipoElemento::PaletaFlipper:
			this->ciclarEntreGiros();
			break;
		case Modelo::TipoElemento::Balancin:
			this->ciclarEntreAngulos();
			break;
		case Modelo::TipoElemento::Tijera:
			this->ciclarEntreGirosTijera();
			break;
		default:
			break;
	}
}

Modelo::TipoElemento FiguraVista::getClase(){
	return this->clase;
}

double FiguraVista::getAnguloRotacion(Vec2 respectoA){
	Vec2 posMouse = respectoA;
	double distX = posMouse.x - this->fuente->getSuperficie().centro().x ;
	double distY = posMouse.y - this->fuente->getSuperficie().centro().y ;
	double result = atan2(distY,distX) * 180 / M_PI;
	return result;
}

vista::Elemento* FiguraVista::clonar() const{
	return new FiguraVista(*this);
}

void FiguraVista::ciclarEntreRadios() {
	FuenteModelo *fuenteActual = dynamic_cast<FuenteModelo*>(fuente.get());
	if (fuenteActual != nullptr) {
		Modelo::EntidadWrapper entidadActual = fuenteActual->getEntidad();

		float radioActual = entidadActual.tamanio().x / 2;
		if (radioActual <= Modelo::Constantes::radioEngranajeS) {
			radioActual = Modelo::Constantes::radioEngranajeM;
		}
		else if (radioActual <= Modelo::Constantes::radioEngranajeM) {
			radioActual = Modelo::Constantes::radioEngranajeL;
		}
		else {
			radioActual = Modelo::Constantes::radioEngranajeS;
		}
		entidadActual.tamanio() = Vec2(2, 2) * radioActual;
	}
}

void FiguraVista::ciclarEntreAngulos()  {
	FuenteModelo *fuenteActual = dynamic_cast<FuenteModelo*>(fuente.get());
	if (fuenteActual != nullptr) {
		Modelo::EntidadWrapper entidadActual = fuenteActual->getEntidad();

		auto iniciales = entidadActual.lugarDondeSePuedeUnir();
		std::vector<Vec2> puntosIniciales(begin(iniciales), end(iniciales));

		float anguloActual = entidadActual.angulo();
		if (anguloActual <= 0) {
			anguloActual = 45;
		} else {
			anguloActual = -45;
		}
		entidadActual.angulo() = anguloActual;

		auto finales = entidadActual.lugarDondeSePuedeUnir();
		std::vector<Vec2> puntosFinales(begin(finales), end(finales));

		auto vinculos = entidadActual.elemPuenteAtado();
		for (Modelo::EntidadWrapper vinculo : vinculos) {
			for (unsigned i = 0; i < puntosIniciales.size(); ++i) {
				if (vinculo.puntoDeLigaduraEntidadA() == puntosIniciales[i]) {
					vinculo.puntoDeLigaduraEntidadA() = puntosFinales[i];
				}
				if (vinculo.puntoDeLigaduraEntidadB() == puntosIniciales[i]) {
					vinculo.puntoDeLigaduraEntidadB() = puntosFinales[i];
				}
				vinculo.regenerar();
			}
		}
	}
}

void FiguraVista::ciclarEntreGiros() {
	FuenteModelo *fuenteActual = dynamic_cast<FuenteModelo*>(fuente.get());
	if (fuenteActual != nullptr) {
		Modelo::EntidadWrapper entidadActual = fuenteActual->getEntidad();
		entidadActual.estadoNormal() = !entidadActual.estadoNormal();
		entidadActual.angulo() = -entidadActual.angulo();
	}
}

void FiguraVista::ciclarEntreGirosTijera() {
	FuenteModelo *fuenteActual = dynamic_cast<FuenteModelo*>(fuente.get());
	if (fuenteActual != nullptr) {
		Modelo::EntidadWrapper entidadActual = fuenteActual->getEntidad();

		auto iniciales = entidadActual.lugarDondeSePuedeUnir();
		std::vector<Vec2> puntosIniciales(begin(iniciales), end(iniciales));

		if (entidadActual.angulo() == (float)270)
			entidadActual.angulo() = 0.0;
		else
			entidadActual.angulo() += 90;

		auto finales = entidadActual.lugarDondeSePuedeUnir();
		std::vector<Vec2> puntosFinales(begin(finales), end(finales));

		auto vinculos = entidadActual.elemPuenteAtado();
		for (Modelo::EntidadWrapper vinculo : vinculos) {
			for (unsigned i = 0; i < puntosIniciales.size(); ++i) {
				if (vinculo.puntoDeLigaduraEntidadA() == puntosIniciales[i]) {
					vinculo.puntoDeLigaduraEntidadA() = puntosFinales[i];
				}
				if (vinculo.puntoDeLigaduraEntidadB() == puntosIniciales[i]) {
					vinculo.puntoDeLigaduraEntidadB() = puntosFinales[i];
				}
				vinculo.regenerar();
			}
		}
	}
}

void FiguraVista::cambiarImagen(std::string path) {
	if (path != pathImagen) {
		imagen = Imagen(path, &imagen);
		pathImagen = path;
	}
}

unsigned FiguraVista::cantEngranajes() const {
	float anchoFig = fuente->getSuperficie().tam().x;
	float diametro = fuente->getSuperficie().tam().y;
	float relacion = anchoFig / diametro;
	// extremos dictados por las imagenes disponibles
	return std::max(2, std::min((int)std::ceil(relacion), 15));
}

unsigned FiguraVista::estadoRotacion() const {
	FuenteModelo *fuente = dynamic_cast<FuenteModelo*>(this->fuente.get());
	if (fuente == nullptr) {
		return 0;
	}
	float distanciaRecorrida = fuente->getEntidad().distanciaRecorrida();
	float angulo = distanciaRecorrida * 4 / M_PI; // angulo con revolucion de 4
	float anguloNormalizado = angulo - 4 * std::round(angulo/4);
	int estadoRotacion = std::floor(anguloNormalizado);
	if (estadoRotacion < 0)
		estadoRotacion += 4;
	return estadoRotacion;
}

void FiguraVista::verificarImagen()
{
	using namespace Modelo;

	if (clase == TipoElemento::CintaTransportadora) {
		cambiarImagen(vista::InfoCinta::imagenes.find(cantEngranajes())->second.at(estadoRotacion()));
		return;
	}

	EntidadWrapper entidad;

	FuenteModelo* fuente = dynamic_cast<FuenteModelo*>(getFuente());
	if (fuente != nullptr) {
		entidad = fuente->getEntidad();
	}

	unsigned delayEntreImagenes = 12;

	switch (clase) {

	case TipoElemento::Tijera:
		if (getFuente()->getEstadoNormal()) {
			cambiarImagen("imagenes/objetos/tijeraAbierta.png");
		} else {
			cambiarImagen("imagenes/objetos/tijeraCerrada.png");
		}
		break;

	case TipoElemento::Motor:
		if (getFuente()->getEstadoNormal()) {
			cambiarImagen("imagenes/objetos/motor.png");
		} else {
			cambiarImagen("imagenes/objetos/motorEspejado.png");
		}
		break;

	case TipoElemento::PaletaFlipper:
		if (getFuente()->getEstadoNormal()) {
			cambiarImagen("imagenes/objetos/paletaFlipperIzq.png");
		} else {
			cambiarImagen("imagenes/objetos/paletaFlipperDer.png");
		}
		break;

	case TipoElemento::MotorRaton: {
		if (entidad.valido()) {
			if (!entidad.accionar()) {
				estadoAnimacion = 0;
				contadorAnimacion = 99;
				if (getFuente()->getEstadoNormal()) {
					cambiarImagen("imagenes/objetos/motorRaton1.png");
				} else {
					cambiarImagen("imagenes/objetos/motorRatonEspejado1.png");
				}
			} else {
				std::string raton = (entidad.estadoNormal()) ? std::string("motorRaton") : std::string("motorRatonEspejado");

				if (estadoAnimacion <= 3 &&  contadorAnimacion >= delayEntreImagenes/2) {
					estadoAnimacion++;
					std::string n = std::to_string(estadoAnimacion);
					std::string pathImagen = std::string("imagenes/objetos/") + raton  + n + ".png";
					cambiarImagen(pathImagen);
					contadorAnimacion = 0;
				} else if (estadoAnimacion <= 3) {
					contadorAnimacion++;
				}

				//Vuelve a la primer imagen
				if (estadoAnimacion == 4) {
					estadoAnimacion = 0;
				}
			}
		}
		break;
	}

	case TipoElemento::Globo: {
		if(entidad.valido() && entidad.estadoNormal()) {
			std::string pathImagen = std::string("imagenes/objetos/globo.png");
			cambiarImagen(pathImagen);
			estadoAnimacion = 0;
			contadorAnimacion = 99;
		}

		if (entidad.valido() && entidad.accionar()) {
			if (estadoAnimacion <= 3  &&  contadorAnimacion >= delayEntreImagenes) {
				estadoAnimacion++;
				std::string n = std::to_string(estadoAnimacion);
				std::string pathImagen = std::string("imagenes/objetos/globo")  + n + ".png";
				cambiarImagen(pathImagen);
				contadorAnimacion = 0;
			}
			else if (estadoAnimacion <= 3) {
				contadorAnimacion++;
			}
		}

		break;
	}
	case TipoElemento::Huevo: {
		if (getFuente()->getEstadoNormal() == false) {
			if (estadoAnimacion <= 3  &&  contadorAnimacion >= delayEntreImagenes) {
				estadoAnimacion++;
				std::string n = std::to_string(estadoAnimacion);
				std::string pathImagen = std::string("imagenes/objetos/huevo")  + n + ".png";
				cambiarImagen(pathImagen);
				contadorAnimacion = 0;
			}
			else if (estadoAnimacion <= 3) {
				contadorAnimacion++;
			} else if (entidad.valido()) {
				entidad.accionar() = true;
			}
		} else {
			estadoAnimacion = 0;
			contadorAnimacion = 99;
		}

		break;
	}
	case TipoElemento::Carrito:
		if (entidad.valido()) {
			if (entidad.accionar()) {
				if (estadoAnimacion <= 3  &&  contadorAnimacion >= delayEntreImagenes) {
					estadoAnimacion++;
					std::string n = std::to_string(estadoAnimacion);
					std::string pathImagen = std::string("imagenes/objetos/carrito")  + n + ".png";
					cambiarImagen(pathImagen);
					contadorAnimacion = 0;
				}
				else if (estadoAnimacion <= 3) {
					contadorAnimacion++;
				}
				if (estadoAnimacion == 3) {
					estadoAnimacion = 0;
				}
			} else {
				estadoAnimacion = 0;
				contadorAnimacion = 99;
			}
		}
		break;

	default:
		break;
	}
}
