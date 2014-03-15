/*
 * PaletaFlipper.h
 *
 *  Created on: Nov 13, 2013
 *      Author: lucia
 */

#ifndef PALETAFLIPPER_H_
#define PALETAFLIPPER_H_
#include "Simulador/Cuerpo.h"
#include "../Constantes.h"
#include <Box2D/Box2D.h>

namespace simulador {

class PaletaFlipper : public Cuerpo {
public:
	PaletaFlipper(b2World* mundo, Modelo::EntidadWrapper entidad);
	PaletaFlipper (const PaletaFlipper&) = delete;
	PaletaFlipper& operator= (const PaletaFlipper&) = delete;
	virtual ~PaletaFlipper();
	void vivir();

private:
	b2Body* crearCuerpo();
	b2Body* crearSoporte(float offset);
	b2RevoluteJoint* rJoint;
	int sentido;
	int contadorLevantarFlipper;
};

} /* namespace simulador */
#endif /* PALETAFLIPPER_H_ */
