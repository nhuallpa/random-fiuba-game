/*
 * CuerpoRotativo.h
 *
 *  Created on: 08/10/2013
 *      Author: stephanie
 */

#ifndef CUERPOROTATIVO_H_
#define CUERPOROTATIVO_H_

#include "Simulador/Cuerpo.h"

namespace simulador {

class CuerpoRotativo: public simulador::Cuerpo {
public:
	CuerpoRotativo(b2Vec2 posInicial, b2World* mundo, float angulo,
			float radio,bool sentidoHorario, bool sentidoAntiHorario, bool isMotor, Modelo::EntidadWrapper entidad);

	CuerpoRotativo (const CuerpoRotativo&) = delete;
	CuerpoRotativo& operator= (const CuerpoRotativo&) = delete;
	virtual ~CuerpoRotativo();

	virtual void setRadio(float radio);
	float getRadio();
	//Lo necesito para usar la correa
	virtual b2RevoluteJoint* getJoint();
	b2Body* getSoporte();

	bool getSentidoHorario();
	bool getSentidoAntihorario();
	void setSentidoHorario(bool sentido);
	void setSentidoAntihorario(bool sentido);

	virtual void setSentidoSegunCuerpoRotativo(CuerpoRotativo* cuerpoRotativo);

protected:
	b2RevoluteJoint* rJoint;
	Vec2 posicion;
	float angulo;
	float radio;
	b2Body* soporte;
	bool sentidoAntihorario;
	bool sentidoHorario;

	b2Body* crearCuerpo(b2World* mundo);
	b2Body* crearSoporte(b2World* mundo);
};

} /* namespace simulador */
#endif /* CUERPOROTATIVO_H_ */
