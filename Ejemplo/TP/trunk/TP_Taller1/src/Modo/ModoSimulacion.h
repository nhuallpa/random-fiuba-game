#ifndef MODOSIMULACION_H_
#define MODOSIMULACION_H_

#include "Modelo/Escenario.h"
#include "Modo/ModoEdicion.h"
#include "Modo/Visor.h"

namespace simulador {
	class Simulador;
}

namespace Modo {

class ModoSimulacion : public Visor
{
public:
	ModoSimulacion ();
	ModoSimulacion (ModoEdicion&&);

	ModoSimulacion (const ModoSimulacion&) = delete;
	ModoSimulacion (ModoSimulacion&&) = default;
	ModoSimulacion& operator= (const ModoSimulacion&) = delete;
	ModoSimulacion& operator= (ModoSimulacion&&) = default;
	virtual ~ModoSimulacion ();

	virtual EstadoJuego estado ();
	virtual EstadoJuego iteracionPrincipal (float ms);
	virtual std::unique_ptr<ModoJuego> transicion(EstadoJuego proximo);

private:
	simulador::Simulador *sim;
	Escenario escenarioBackup;
	float ultimaSimulacion;

	friend class ModoEdicion;
};

} /* namespace Modo */
#endif /* MODOSIMULACION_H_ */
