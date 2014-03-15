#ifndef CLICKINFO_H_
#define CLICKINFO_H_

#include "Utils/Vec2.h"

class Contenedor;

namespace vista {

class Elemento;

struct ClickInfo
{
	ClickInfo ();
	ClickInfo (vista::Elemento *clickeado, Vec2 posicionClick);

	ClickInfo (const ClickInfo&) = default;
	ClickInfo (ClickInfo&&) = default;
	ClickInfo& operator= (const ClickInfo&) = default;
	ClickInfo& operator= (ClickInfo&&) = default;
	~ClickInfo () = default;

	bool puedeArrastrar; //false
	bool puedeRotar; //false
	bool puedeResizear; //false
	bool puedeUnirse; //false
	bool iniciaClickeo; //false
	bool tomaFocoTeclado; //true
	bool esCanvas; //false
	bool esBotonCambiante; //false

	vista::Elemento *clickeado;
	Vec2 posicionClick;
};

} /* namespace vista */
#endif /* CLICKINFO_H_ */
