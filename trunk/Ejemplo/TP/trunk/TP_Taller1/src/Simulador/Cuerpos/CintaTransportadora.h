/*
 * CintaTransportadora.h
 *
 *  Created on: 04/10/2013
 *      Author: stephanie
 */

#ifndef CINTATRANSPORTADORA_H_
#define CINTATRANSPORTADORA_H_

#include "Simulador/Cuerpo.h"

namespace simulador {

class CuerpoRotativo;

class CintaTransportadora: public simulador::Cuerpo {
public:
	CintaTransportadora(b2World* mundo, Modelo::EntidadWrapper entidad);

	CintaTransportadora (const CintaTransportadora&) = delete;
	CintaTransportadora& operator= (const CintaTransportadora&) = delete;
	virtual ~CintaTransportadora();

	void vivir();
	void setSentidoSegunCuerpoRotativo(CuerpoRotativo* cuerpoRotativo);

private:

	void crearCinta(b2World* mundo);
	b2Body* crearBox(float x, float y, float ancho);
	void modelarContacto();
	void setearVelocidad();

	Vec2 posicion;
	Vec2 dimensiones;

	b2Body* rectArriba;
	b2Body* rectAbajo;

	Engranaje* gear1;
	Engranaje* gear2;
	float impulso;
	CuerpoRotativo* conectadoACuerpo;
	float velocidad;
	bool engranajesSeteados;

};

} /* namespace simulador */
#endif /* CINTATRANSPORTADORA_H_ */
