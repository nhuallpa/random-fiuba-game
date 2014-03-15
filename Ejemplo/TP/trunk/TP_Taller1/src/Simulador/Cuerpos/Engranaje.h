/*
 * Engranaje.h
 *
 *  Created on: 04/10/2013
 *      Author: stephanie
 */

#ifndef ENGRANAJE_H_
#define ENGRANAJE_H_

#include "Simulador/Cuerpos/CuerpoRotativo.h"
#include <set>

namespace simulador {

class Engranaje: public CuerpoRotativo {
public:
	Engranaje(b2Vec2 posInicial, b2World* mundo,
			float angulo, float radio, bool sentidoHorario,
			bool sentidoAntihorario, Modelo::EntidadWrapper entidad);
	void tocarse(Cuerpo* otroCuerpo, b2World* mundo);
	void conectarA(Engranaje* eng, b2World* mundo);
	virtual ~Engranaje();
	void insertarConexion(Cuerpo* otroCuerpo);
	void vivir();

private:
	std::set<Cuerpo*> cuerposConectadosAMi;
};

} /* namespace simulador */
#endif /* ENGRANAJE_H_ */
