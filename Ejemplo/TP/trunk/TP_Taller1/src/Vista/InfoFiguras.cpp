#include "Vista/InfoFiguras.h"

using namespace Modelo;

namespace vista {

InfoFiguras::InfoFiguras ()
	: tipo()
	, pathImagenToolbar()
	, pathImagenCanvas()
	, tamCanvas()
	, anguloCanvas()
{
}

InfoFiguras::InfoFiguras (Modelo::TipoElemento tipo,
                          std::string pathImagenToolbar,
                          std::string pathImagenCanvas,
                          Vec2 tamCanvas,
                          float anguloCanvas)
	: tipo(tipo)
	, pathImagenToolbar(pathImagenToolbar)
	, pathImagenCanvas(pathImagenCanvas)
	, tamCanvas(tamCanvas)
	, anguloCanvas(anguloCanvas)
{
}

std::map<TipoElemento, InfoFiguras> InfoFiguras::datos = {
	{TipoElemento::PelotaBasquet, {TipoElemento::PelotaBasquet
			, "imagenes/objetos/pelotaBasquet.png"
			, "imagenes/objetos/pelotaBasquet.png"
			, Vec2(1, 1)
			, 0}},
	{TipoElemento::PelotaBowling, {TipoElemento::PelotaBowling
			, "imagenes/objetos/pelotaBowling.png"
			, "imagenes/objetos/pelotaBowling.png"
			, Vec2(1, 1)
			, 0}},
	{TipoElemento::Balancin, {TipoElemento::Balancin
			, "imagenes/objetos/balancin.png"
			, "imagenes/objetos/balancin.png"
			, Vec2(3, 0.5)
			, 0}},
	{TipoElemento::CintaTransportadora, {TipoElemento::CintaTransportadora
			, "imagenes/objetos/cintaTransportadora.png"
			, "imagenes/objetos/cintaTransportadora.png"
			, Vec2(3, 0.8)
			, 0}},
	{TipoElemento::Correa, {TipoElemento::Correa
			, "imagenes/objetos/correa.png"
			, "imagenes/objetos/correa.png"
			, Vec2(1, 0.5)
			, 0}},
	{TipoElemento::Globo, {TipoElemento::Globo
			, "imagenes/objetos/globo.png"
			, "imagenes/objetos/globo.png"
			, Vec2(0.9, 1)
			, 0}},
	{TipoElemento::Motor, {TipoElemento::Motor
			, "imagenes/objetos/motor.png"
			, "imagenes/objetos/motor.png"
			, Vec2(1.7, 1.4)
			, 0}},
	{TipoElemento::Plataforma, {TipoElemento::Plataforma
			, "imagenes/objetos/plataformaMadera.png"
			, "imagenes/objetos/plataformaMadera.png"
			, Vec2(3, 0.5)
			, 0}},
	{TipoElemento::Soga, {TipoElemento::Soga
			, "imagenes/objetos/soga.png"
			, "imagenes/objetos/soga.png"
			, Vec2(1, 0.15)
			, 0}},
	{TipoElemento::Engranaje, {TipoElemento::Engranaje
			, "imagenes/objetos/engranajeM.png"
			, "imagenes/objetos/engranajeM.png"
			, Vec2(1, 1)
			, 0}},
	/*----------------------------------------------------------*/
	{TipoElemento::Clavo, {TipoElemento::Clavo
			, "imagenes/objetos/clavo.png"
			, "imagenes/objetos/clavo.png"
			, Vec2(0.45, 0.45)
			, 180}},
	{TipoElemento::Yunque, {TipoElemento::Yunque
			, "imagenes/objetos/yunque.png"
			, "imagenes/objetos/yunque.png"
			, Vec2(2, 1)
			, 0}},
	{TipoElemento::Tijera, {TipoElemento::Tijera
			, "imagenes/objetos/tijeraAbierta.png"
			, "imagenes/objetos/tijeraAbierta.png"
			, Vec2(1.3, 1.1)
			, 0}},
	{TipoElemento::Polea, {TipoElemento::Polea
			, "imagenes/objetos/polea.png"
			, "imagenes/objetos/polea.png"
			, Vec2(1.4, 1.4)
			, 0}},
	{TipoElemento::Gancho, {TipoElemento::Gancho
			, "imagenes/objetos/gancho.png"
			, "imagenes/objetos/gancho.png"
			, Vec2(0.5, 0.5)
			, 0}},
	/*----------------------------------------------------------*/
	{TipoElemento::Huevo, {TipoElemento::Huevo
			, "imagenes/objetos/huevo.png"
			, "imagenes/objetos/huevo.png"
			, Vec2(0.6, 0.6)
			, 0}},
	{TipoElemento::Canio, {TipoElemento::Canio
			, "imagenes/objetos/canio10t.png"
			, "imagenes/objetos/canio10t.png"
			, Vec2(2.5, 1.5)
			, 0}},
	{TipoElemento::Codo, {TipoElemento::Codo
			, "imagenes/objetos/codo10t.png"
			, "imagenes/objetos/codo10t.png"
			, Vec2(2.5, 2.5)
			, 0}},
	{TipoElemento::Domino, {TipoElemento::Domino
			, "imagenes/objetos/domino.png"
			, "imagenes/objetos/domino.png"
			, Vec2(0.15, 0.6)
			, 0}},
	{TipoElemento::Vela, {TipoElemento::Vela
			, "imagenes/objetos/vela.png"
			, "imagenes/objetos/vela.png"
			, Vec2(0.5, 1)
			, 0}},
	{TipoElemento::Carrito, {TipoElemento::Carrito
			, "imagenes/objetos/carrito1.png"
			, "imagenes/objetos/carrito1.png"
			, Vec2(2, 1.2)
			, 0}},
	{TipoElemento::MotorRaton, {TipoElemento::MotorRaton
			, "imagenes/objetos/motorRaton1.png"
			, "imagenes/objetos/motorRaton1.png"
			, Vec2(1.7, 1.2)
			, 0}},
	{TipoElemento::Queso, {TipoElemento::Queso
			, "imagenes/objetos/queso.png"
			, "imagenes/objetos/queso.png"
			, Vec2(1, 0.8)
			, 0}},
	/*----------------------------------------------------------*/
	{TipoElemento::PaletaFlipper, {TipoElemento::PaletaFlipper
			, "imagenes/objetos/paletaFlipperIzq.png"
			, "imagenes/objetos/paletaFlipperIzq.png"
			, Vec2(1.9, 0.8)
			, 30}},
	/*----------------------------------------------------------*/
	{TipoElemento::Canasto, {TipoElemento::Canasto
			, "imagenes/objetos/canasto.png"
			, "imagenes/objetos/canasto.png"
			, Vec2(1.7, 1.7)
			, 0}},
};

} /* namespace vista */
