#include "ClickInfo.h"

namespace vista {

ClickInfo::ClickInfo()
	: puedeArrastrar(false)
	, puedeRotar(false)
	, puedeResizear(false)
	, puedeUnirse(false)
	, iniciaClickeo(false)
	, tomaFocoTeclado(true)
	, esCanvas(false)
	, esBotonCambiante(false)
	, clickeado(nullptr)
	, posicionClick()
{
}

ClickInfo::ClickInfo(vista::Elemento *clickeado, Vec2 posicionClick)
	: puedeArrastrar(false)
	, puedeRotar(false)
	, puedeResizear(false)
	, puedeUnirse(false)
	, iniciaClickeo(false)
	, tomaFocoTeclado(true)
	, esCanvas(false)
	, esBotonCambiante(false)
	, clickeado(clickeado)
	, posicionClick(posicionClick)
{
}

} /* namespace vista */
