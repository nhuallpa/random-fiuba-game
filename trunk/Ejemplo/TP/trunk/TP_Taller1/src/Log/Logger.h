#ifndef LOGGER_H_
#define LOGGER_H_

#include "Level.h"
#include "Threads/Atomic.h"

#include <string>
#include <iosfwd>
#include <list>

namespace Log
{

class Suceso;

/* Recibe sucesos globalmente mientras exista, los imprime a out si son la clase
 * de sucesos que indica la mascara en mostrados */
class Logger
{
public:
	Logger (int mostrados);
	Logger (std::string filename, int mostrados);
	virtual ~Logger ();

	int& nivelesMostrados ();

protected:
	std::string time_msg (time_t hora) const;
	const char* level_msg (int interseccion) const;

private:
	bool porEstandar;
	std::string filename;
	int mostrados;
	static Threads::Atomic<std::list<Logger*>> activos;

	void print (const Suceso *s) const;
	static void throw_suceso (const Suceso *s);

	friend class Suceso;
};


} /* namespace Log */
#endif /* LOGGER_H_ */
