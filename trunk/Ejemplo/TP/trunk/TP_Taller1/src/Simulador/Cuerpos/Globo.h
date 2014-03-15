/*
 * Globo.h
 *
 *  Created on: Oct 4, 2013
 *      Author: lucia
 */

#ifndef GLOBO_H_
#define GLOBO_H_
#include "Pelota.h"
namespace simulador {

//Implementa pelota porque básicamente es una pelota de helio.
class Globo: public Pelota {
public:
	Globo(b2World* mundo, Modelo::EntidadWrapper entidad);
	void vivir();
	virtual ~Globo();
private:
	Cuerpo* buscarCuerpoEnMundo(Modelo::EntidadWrapper entidad);
	bool exploto;
};

} /* namespace simulador */
#endif /* GLOBO_H_ */
