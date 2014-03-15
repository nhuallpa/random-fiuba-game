#ifndef SUCESO_H_
#define SUCESO_H_

#include "Level.h"

#include <string>
#include <stdexcept>

namespace Log
{

class Suceso : public std::exception
{
public:
	Suceso (Level nivel, std::string mensaje);
	virtual ~Suceso () throw ();

	Level nivel () const;
	const std::string& mensaje () const;
	time_t hora () const;

	const char *what () const throw ();

protected:
	Level _nivel;
	std::string _mensaje;
	time_t _hora;
};

} /* namespace Log */
#endif /* SUCESO_H_ */
