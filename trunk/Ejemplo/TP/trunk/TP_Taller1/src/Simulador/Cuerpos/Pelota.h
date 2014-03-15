/*
 * Pelota.h
 *
 *  Created on: Oct 3, 2013
 *      Author: lucia
 */

#ifndef PELOTA_H_
#define PELOTA_H_
#include "Simulador/Cuerpo.h"

namespace simulador {

class Pelota : public Cuerpo{
public:
	Pelota(float coefRestitucion, float densidad, b2World* mundo, Modelo::EntidadWrapper entidad);
	virtual ~Pelota();
	void vivir();

protected:
	float coeficienteRestitucion;
	float densidad;
	float radio;
	float anguloInicial;

private:
	b2Body* crearCuerpo(b2World* mundo);
};

} /* namespace simulador */
#endif /* PELOTA_H_ */
