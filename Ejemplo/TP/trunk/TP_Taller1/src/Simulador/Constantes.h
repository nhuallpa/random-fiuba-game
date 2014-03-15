/*
 * Constantes.h
 *
 *  Created on: Oct 4, 2013
 *      Author: lucia
 */

#ifndef CONSTANTES_H_
#define CONSTANTES_H_

namespace simulador {

/* ACA VAN TODAS LAS CONSTANTES DE LA SIMULACION
 * USAGE: Constantes::Instancia()->constanteRequerida
 * */
class Constantes {
public:

	static Constantes* Instancia();

	static float iteracionesPorSegundo;
	static float nIteracionesVelocidades;
	static float nIteracionesPosiciones;
	static float delta;
	static float gravedad;
	static float friccionGenerica;
	static float densidadGenerica;
	static float dampingAire;
	static float densidadAire;
	static float densidadPelotaBasquet;
	static float densidadPelotaBowling;
	static float densidadPaletaFlipper;
	static float densidadPolea;
	static float densidadGancho;
	static float densidadYunque;
	static float radioPelotaBasquet;
	static float radioPelotaBowling;
	static float radioSoporte;
	static float coeficienteRestitucionPelotaBasquet;
	static float coeficienteRestitucionPolea;
	static float coeficienteRestitucionPelotaBowling;
	static float coeficienteRestitucionGlobo;
	static float radioGlobo;
	static float radioMotor;
	static float densidadGlobo;
	static float motorSpeed;
	static float maxMotorTorque;
	static float ratioGiroEngranajes;
	static float densidadCuerpoRotativo;
	static float DEGTORAD;
	static float RADTODEG;
	static float aceleracionCinta;
	static float distanciaMinimaQueso;

protected:
	Constantes () {};
	Constantes (Constantes const&) = delete;
	Constantes& operator=(Constantes const&) = delete;
private:
	static Constantes* _instance;

};


} /* namespace simulador */
#endif /* CONSTANTES_H_ */
