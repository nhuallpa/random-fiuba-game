#ifndef AVISO_H_
#define AVISO_H_

#include "Modo/ModoUsuario.h"
#include "Vista/Contenedor.h"
#include <string>

class Contenedor;

namespace Modo {

enum class TipoAviso : uint8_t {
	Mision,
	Win,
	Error,
};

class Aviso : public ModoJuego
{
public:
	Aviso ();
	Aviso (std::unique_ptr<ModoJuego> anterior, TipoAviso tipo, std::string mensaje);
	virtual ~Aviso();

	virtual EstadoJuego estado ();
	virtual EstadoJuego iteracionPrincipal (float ms);
	virtual std::unique_ptr<ModoJuego> transicion(EstadoJuego proximo);

private:
	std::unique_ptr<Contenedor> contenedorVentana;
	std::unique_ptr<ModoJuego> anterior;

	TipoAviso tipoAviso;
	std::string mensaje;
	bool aceptado_;

	static Vec2 getTamanio(TipoAviso tipoAviso);
};

} /* namespace Modo */
#endif /* AVISO_H_ */
