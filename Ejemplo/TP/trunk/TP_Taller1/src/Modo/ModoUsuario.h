#ifndef MODOJUEGO_H_
#define MODOJUEGO_H_

#include <memory>

class Ventana;

namespace Modo {

class Aviso;

enum class EstadoJuego : size_t
{
	edicion,     // [inicial] simulacion, visor
	simulacion,  // edicion
	visor,       // edicion
	aviso,       // (absorbe un modo)
};

class ModoJuego
{
public:
	explicit ModoJuego (Ventana *window) : window(window) {};

	ModoJuego (const ModoJuego&) = delete;
	ModoJuego (ModoJuego&&) = default;
	ModoJuego& operator= (const ModoJuego&) = delete;
	ModoJuego& operator= (ModoJuego&&) = default;
	virtual ~ModoJuego() {};

	// devuelve el estado actual de juego
	virtual EstadoJuego estado () = 0;
	// realiza una iteracion de su ciclo principal correspondiente a un tiempo dt
	// devuelve el proximo estado de juego
	virtual EstadoJuego iteracionPrincipal (float ms) = 0;
	// invalida la interfaz sobre la que se llama
	virtual std::unique_ptr<ModoJuego> transicion(EstadoJuego proximo) = 0;

protected:
	Ventana *window;
	friend class Aviso;
};

} /* namespace Modo */
#endif /* MODOJUEGO_H_ */
