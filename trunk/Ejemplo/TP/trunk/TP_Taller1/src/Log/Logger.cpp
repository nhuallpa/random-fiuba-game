#include "Logger.h"

#include "Suceso.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

namespace Log
{

Threads::Atomic<std::list<Logger*>> Logger::activos;

Logger::Logger (int mostrados)
	: porEstandar(true)
	, filename()
	, mostrados(mostrados)
{
	activos.transform([&] (std::list<Logger*> lista) {
		lista.push_back(this);
		return lista;
	});
}

Logger::Logger (std::string filename, int mostrados)
	: porEstandar(false)
	, filename(filename)
	, mostrados(mostrados)
{
	activos.transform([&] (std::list<Logger*> lista) {
		lista.push_back(this);
		return lista;
	});
}

Logger::~Logger ()
{
	activos.transform([&] (std::list<Logger*> lista) {
		lista.remove(this);
		return lista;
	});
}

int& Logger::nivelesMostrados ()
{
	return mostrados;
}

void Logger::print (const Suceso *s) const
{
	std::ostream *out;
	if (porEstandar) {
		out = &std::cout;
	} else {
		out = new std::ofstream(filename.c_str(), std::ios_base::app);
	}

	int interseccion = s->nivel() & mostrados;
	if (interseccion) {
		(*out) << time_msg(s->hora()) << " "
		       << level_msg(interseccion) << ": "
		       << s->mensaje() << std::endl;
	}

	if (!porEstandar) {
		delete out;
	}
}

std::string Logger::time_msg (time_t hora) const
{
	std::ostringstream salida;

	std::string separadorFecha = "/";
	std::string separadorHora = ":";

	struct tm *val = localtime(&hora);

	salida.fill('0');
	salida << (1900 + val->tm_year) << separadorFecha
	       << std::setw(2) << val->tm_mon << separadorFecha
	       << std::setw(2) << val->tm_mday << " "
	       << std::setw(2) << val->tm_hour << separadorHora
	       << std::setw(2) << val->tm_min << separadorHora
	       << std::setw(2) << val->tm_sec;

	return salida.str();
}

const char* Logger::level_msg (int i) const
{
	if (i & FATAL) {
		return "FATAL";
	} else if (i & ERROR) {
		return "ERROR";
	} else if (i & WARN) {
		return "Error";
	} else if (i & INFO) {
		return "Info";
	} else if (i & DEBUG) {
		return "debug";
	} else {
		throw Suceso(FATAL, "Nivel de loggeo desconocido");
	}
}

void Logger::throw_suceso (const Suceso *s)
{
	activos.transform([&] (std::list<Logger*> lista) {
		for (Logger* log : lista) {
			log->print(s);
		}
		return lista;
	});
}

} /* namespace Log */
