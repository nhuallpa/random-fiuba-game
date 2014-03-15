#ifndef VISOR_H_
#define VISOR_H_

#include "Modelo/Escenario.h"
#include "Modo/ModoUsuario.h"
#include "Modo/ModoEdicion.h"

class Contenedor;
class Escenario;
class Textura;
class Ventana;
namespace Modelo {
	class Juego;
}

namespace Modo {

class Visor : public ModoJuego
{
public:
	Visor ();
	Visor (ModoEdicion&&);

	Visor (const Visor&) = delete;
	Visor (Visor&&) = default;
	Visor& operator= (const Visor&) = delete;
	Visor& operator= (Visor&&) = default;
	virtual ~Visor ();

	virtual EstadoJuego estado ();
	virtual EstadoJuego iteracionPrincipal (float ms);
	virtual std::unique_ptr<ModoJuego> transicion(EstadoJuego proximo);

protected:
	Modelo::Juego *juego;
	std::string pathEscenario;
	Canvas *canvas;
	Boton *cambioModo;
	EstadoJuego proximoEstado;
	float ultimoGrafico;

	static constexpr unsigned fps_deseado = 60;

	friend class ModoEdicion;
};

} /* namespace Modo */
#endif /* VISOR_H_ */
