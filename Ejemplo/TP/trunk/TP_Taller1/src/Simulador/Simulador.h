/*
 * Simulador.h
 *
 *  Created on: Oct 5, 2013
 *      Author: lucia
 */

#ifndef SIMULADOR_H_
#define SIMULADOR_H_
#include <list>
#include "ContactListener.h"

namespace Modelo {
	class EntidadWrapper;
	class Mundo;
}
class b2World;

namespace simulador {

class Cuerpo;

class Simulador {
public:
	Simulador(Modelo::Mundo* mundo);

	Simulador (const Simulador&) = delete;
	Simulador& operator= (const Simulador&) = delete;
	virtual ~Simulador();

	//Da un paso en la simulación.
	bool step();
	float getTimeStep ();

private:
	void modelarMundo(Modelo::Mundo* mundo);
	void modelarCuerpos(Modelo::Mundo* mundo);
	void modelarContactos();
	float timeStep;      //el tiempo entre simulaciones
	int velocityIterations;   //esto tiene que ver con cuantas iteraciones
	int positionIterations;

	b2World* m_mundo;
	//Lista de cuerpos que se va a recorrer y hacer vivir en
	//cada step del simulador.
	std::list<Cuerpo*> cuerpos;

	Cuerpo* buscarCuerpo(Modelo::EntidadWrapper entidad);
	void modelarContactosADistancia(std::list<Modelo::EntidadWrapper> uniones);
	void modelarCuerpoRotativoCinta(Modelo::EntidadWrapper entidad);
	void modelarCuerposRotativos(Modelo::EntidadWrapper entidad);
	void modelarPolea(Modelo::EntidadWrapper entidad);
	void modelarTijera(Modelo::EntidadWrapper entidad);

	Modelo::Mundo* mundoModelo;

	ContactListener contactListener;
};

} /* namespace simulador */
#endif /* SIMULADOR_H_ */
