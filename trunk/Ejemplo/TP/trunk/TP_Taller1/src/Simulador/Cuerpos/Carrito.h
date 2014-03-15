/*
 * Carrito.h
 *
 *  Created on: 29/11/2013
 *      Author: stephanie
 */

#ifndef CARRITO_H_
#define CARRITO_H_

#include "Simulador/Cuerpo.h"

namespace simulador {

class Carrito: public simulador::Cuerpo {
public:
	Carrito(b2World* mundo, Modelo::EntidadWrapper entidad);
	Carrito (const Carrito&) = delete;
	Carrito& operator= (const Carrito&) = delete;
	void vivir();
	virtual ~Carrito();
private:
	b2Body* m_rueda1;
	b2Body* m_rueda2;
};

} /* namespace simulador */
#endif /* CARRITO_H_ */
