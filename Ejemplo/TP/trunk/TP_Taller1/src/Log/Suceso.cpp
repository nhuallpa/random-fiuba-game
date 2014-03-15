#include "Suceso.h"

#include "Logger.h"

namespace Log
{

Suceso::Suceso (Level nivel, std::string mensaje)
	: _nivel(nivel)
	, _mensaje(mensaje)
	, _hora(time(0))
{
	Logger::throw_suceso(this);
}

Suceso::~Suceso () throw ()
{
}

Level Suceso::nivel () const
{
	return _nivel;
}

const std::string& Suceso::mensaje () const
{
	return _mensaje;
}

time_t Suceso::hora () const
{
	return _hora;
}

const char *Suceso::what () const throw ()
{
	return _mensaje.c_str();
}

} /* namespace Log */
