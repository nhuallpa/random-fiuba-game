#ifndef MODOEDICION_H_
#define MODOEDICION_H_

#include "Modo/ModoUsuario.h"

#include <string>

namespace Modelo {
	class Juego;
}
class Boton;
class Canvas;
class Ventana;

namespace Modo {

class Visor;

class ModoEdicion : public ModoJuego
{
public:
	ModoEdicion ();
	ModoEdicion (Ventana *ventana, Modelo::Juego *juego, std::string pathEscenario);

	ModoEdicion (const ModoEdicion&) = delete;
	ModoEdicion (ModoEdicion&&) = default;
	ModoEdicion& operator= (const ModoEdicion&) = delete;
	ModoEdicion& operator= (ModoEdicion&&) = default;
	virtual ~ModoEdicion();

	virtual EstadoJuego estado ();
	virtual EstadoJuego iteracionPrincipal (float ms);
	virtual std::unique_ptr<ModoJuego> transicion(EstadoJuego proximo);

private:
	Modelo::Juego *juego;
	std::string pathEscenario;
	Canvas *canvas;
	Boton *cambioModo;
	EstadoJuego proximoEstado;
	float ultimoUpdate;

	static constexpr unsigned fps_deseado = 60;

	friend class ModoSimulacion;
	friend class Visor;
};

} /* namespace Modo */
#endif /* MODOEDICION_H_ */
