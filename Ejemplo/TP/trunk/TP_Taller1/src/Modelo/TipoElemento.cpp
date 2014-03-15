#include "TipoElemento.h"

#include "Log/Suceso.h"
#include <list>
#include <utility>

namespace Modelo {


std::list<TipoElemento> listaTipoElemento = {
	TipoElemento::PelotaBasquet,
	TipoElemento::PelotaBowling,
	TipoElemento::Globo,
	TipoElemento::Plataforma,
	TipoElemento::Balancin,
	TipoElemento::Soga,
	TipoElemento::Motor,
	TipoElemento::Correa,
	TipoElemento::Engranaje,
	TipoElemento::CintaTransportadora,

	TipoElemento::Yunque,
	TipoElemento::Gancho,
	TipoElemento::Tijera,
	TipoElemento::Clavo,
	TipoElemento::Polea,

	TipoElemento::Huevo,
	TipoElemento::Canio,
	TipoElemento::Codo,
	TipoElemento::Carrito,
//	TipoElemento::Dinamita,
//	TipoElemento::Detonador,
	TipoElemento::Domino,
	TipoElemento::Vela,
//	TipoElemento::Escopeta,
//	TipoElemento::Arco,
//	TipoElemento::Flecha,
	TipoElemento::MotorRaton,
	TipoElemento::Queso,

//	TipoElemento::BombaRemota,
	TipoElemento::PaletaFlipper,
//	TipoElemento::MotorAdistancia

	TipoElemento::Canasto
};


/* static en variable global := solo visible desde esta unidad de compilacion */
static std::list<std::pair<TipoElemento, std::string>> valores = {
	make_pair(TipoElemento::PelotaBasquet, std::string("PelotaBasquet")),
	make_pair(TipoElemento::PelotaBowling, std::string("PelotaBowling")),
	make_pair(TipoElemento::Globo, std::string("Globo")),
	make_pair(TipoElemento::Plataforma, std::string("Plataforma")),
	make_pair(TipoElemento::Balancin, std::string("Balancin")),
	make_pair(TipoElemento::Soga, std::string("Soga")),
	make_pair(TipoElemento::Motor, std::string("Motor")),
	make_pair(TipoElemento::Correa, std::string("Correa")),
	make_pair(TipoElemento::Engranaje, std::string("Engranaje")),
	make_pair(TipoElemento::CintaTransportadora, std::string("CintaTransportadora")),

	make_pair(TipoElemento::Yunque, std::string("Yunque")),
	make_pair(TipoElemento::Gancho, std::string("Gancho")),
	make_pair(TipoElemento::Tijera, std::string("Tijera")),
	make_pair(TipoElemento::Clavo, std::string("Clavo")),
	make_pair(TipoElemento::Polea, std::string("Polea")),

	make_pair(TipoElemento::Huevo, std::string("Huevo")),
	make_pair(TipoElemento::Canio, std::string("Canio")),
	make_pair(TipoElemento::Codo, std::string("Codo")),
	make_pair(TipoElemento::Carrito, std::string("Carrito")),
//	make_pair(TipoElemento::Dinamita, std::string("Dinamita")),
//	make_pair(TipoElemento::Detonador, std::string("Detonador")),
	make_pair(TipoElemento::Domino, std::string("Domino")),
	make_pair(TipoElemento::Vela, std::string("Vela")),
//	make_pair(TipoElemento::Escopeta, std::string("Escopeta")),
//	make_pair(TipoElemento::Arco, std::string("Arco")),
//	make_pair(TipoElemento::Flecha, std::string("Flecha")),
	make_pair(TipoElemento::MotorRaton, std::string("MotorRaton")),
	make_pair(TipoElemento::Queso, std::string("Queso")),

//	make_pair(TipoElemento::BombaRemota, std::string("BombaRemota")),
	make_pair(TipoElemento::PaletaFlipper, std::string("PaletaFlipper")),
//	make_pair(TipoElemento::MotorAdistancia, std::string("MotorAdistancia"))

	make_pair(TipoElemento::Canasto, std::string("Canasto"))
};


std::string tipoElementoToString(TipoElemento clase) {
	for (auto par : valores) {
		if (par.first == clase) {
			return par.second;
		}
	}
	throw Log::Suceso(Log::DEBUG, "Se intento convertir clase desconocida a string.");
}


TipoElemento stringToTipoElemento(std::string clase) {
	for (auto par : valores) {
		if (par.second == clase) {
			return par.first;
		}
	}
	std::string mensaje = std::string("Se intento convertir el string desconocido ")
		+ "'" + clase + "'" + " a clase.";
	throw Log::Suceso(Log::ERROR, mensaje);
}

bool esMovil (TipoElemento clase)
{
	switch (clase) {
	case TipoElemento::Balancin:
	case TipoElemento::Canio:
	case TipoElemento::CintaTransportadora:
	case TipoElemento::Clavo:
	case TipoElemento::Codo:
	case TipoElemento::Engranaje:
	case TipoElemento::Gancho:
	case TipoElemento::Motor:
	case TipoElemento::PaletaFlipper:
	case TipoElemento::Plataforma:
	case TipoElemento::Polea:
	case TipoElemento::Tijera:
	case TipoElemento::MotorRaton:
	case TipoElemento::Canasto:
		return false;

	case TipoElemento::Correa:
	case TipoElemento::Soga:
		return true;

	case TipoElemento::Domino:
	case TipoElemento::Globo:
	case TipoElemento::Huevo:
	case TipoElemento::PelotaBasquet:
	case TipoElemento::PelotaBowling:
	case TipoElemento::Queso:
	case TipoElemento::Vela:
	case TipoElemento::Yunque:
	case TipoElemento::Carrito:
		return true;
	}
	throw Log::Suceso(Log::DEBUG, "Clase desconocida en esMovil");
}

bool esNoMovil (TipoElemento clase)
{
	return !esMovil(clase);
}

bool esElementoPuente (TipoElemento clase)
{
	switch (clase) {
	case TipoElemento::Correa:
	case TipoElemento::Soga:
		return true;

	default:
		return false;
	}
}

bool esSogeable (TipoElemento clase)
{
	switch (clase) {
	case TipoElemento::Balancin:
	case TipoElemento::Gancho:
	case TipoElemento::Globo:
	case TipoElemento::Polea:
	case TipoElemento::Tijera:
	case TipoElemento::Yunque:
	case TipoElemento::Carrito:
		return true;

	default:
		return false;
	}
}

bool esCorreable (TipoElemento clase)
{
	switch (clase) {
	case TipoElemento::CintaTransportadora:
	case TipoElemento::Engranaje:
	case TipoElemento::Motor:
	case TipoElemento::MotorRaton:
		return true;

	default:
		return false;
	}
}

bool esInteractivo (TipoElemento clase)
{
	switch (clase) {
	case TipoElemento::PaletaFlipper:
		return true;

	default:
		return false;
	}
}

bool esAtravesable (TipoElemento clase)
{
	switch (clase) {
	case TipoElemento::Canio:
	case TipoElemento::Codo:
	case TipoElemento::Canasto:
		return true;

	default:
		return false;
	}
}

} /* namespace Modelo */
