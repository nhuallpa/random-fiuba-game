/*
 * Constantes.cpp
 *
 *  Created on: Oct 4, 2013
 *      Author: lucia
 */

#include "Constantes.h"
#include <cmath>

namespace simulador {

//Constantes del simulador en general y del mundo
Constantes* Constantes::_instance = nullptr;
//Estos 60, 8 y 3 son los recomendados por el manual.
float Constantes::iteracionesPorSegundo = 60;
float Constantes::nIteracionesVelocidades = 8;
float Constantes::nIteracionesPosiciones = 3;
float Constantes::gravedad = 9.8;

//Constantes para los cuerpos
//Quizas la friccion debería ser mayor.
float Constantes::friccionGenerica = 1;
float Constantes::densidadGenerica = 1;
float Constantes::densidadPaletaFlipper = 400;
float Constantes::dampingAire = 1;
float Constantes::densidadAire = 1.225;
float Constantes::densidadPelotaBasquet = 80;
float Constantes::densidadPelotaBowling = 240;
float Constantes::densidadPolea = 150;
float Constantes::densidadGlobo = 1;
float Constantes::densidadGancho = 150;
float Constantes::densidadYunque = 400;
float Constantes::coeficienteRestitucionPelotaBasquet = 0.80;
float Constantes::coeficienteRestitucionPelotaBowling = 0.25;
float Constantes::coeficienteRestitucionPolea = 0.50;
float Constantes::radioSoporte = 0;
float Constantes::coeficienteRestitucionGlobo = 0.50;
float Constantes::densidadCuerpoRotativo = 10;
float Constantes::motorSpeed = 10;
float Constantes::maxMotorTorque = 50000000;
float Constantes::ratioGiroEngranajes = 1;
float Constantes::distanciaMinimaQueso = 6;

//Constantes generales
float Constantes::DEGTORAD = 0.0174532925199432957f;
float Constantes::RADTODEG = 57.295779513082320876f;

Constantes* Constantes::Instancia(){
	if(!_instance) {
		_instance = new Constantes();
	}
	return _instance;
}


} /* namespace simulador */
