#include "Log.h"
#include "./Constantes/Constantes.h"
#include <fstream>
#include <ctime>
#include <cstdarg>
#include <cstdio>

Log::Log(void)
{
}

Log::~Log(void)
{
}

//Public


/*LOGGER GENERICO*/
void Log::d(char* form, ...)
{
	va_list argumentos;
	va_start(argumentos,form);
	Log::d(Log::stringConFormato(form,argumentos));
}

void Log::e(char* form, ...)
{
	va_list argumentos;
	va_start(argumentos,form);
	Log::e(Log::stringConFormato(form,argumentos));
}

void Log::d(std::string msj)
{
	Log::log(DEBUG,NO_DEFINIDO,msj);
}

void Log::e(std::string msj)
{
	Log::log(ERROR,NO_DEFINIDO,msj);
}


/*PARA AGREGAR LUGAR*/
void Log::d(LugarLog lugarLog,char* form, ...)
{
	va_list argumentos;
	va_start(argumentos,form);
	Log::d(lugarLog,Log::stringConFormato(form,argumentos));
}

void Log::e(LugarLog lugarLog,char* form, ...)
{
	va_list argumentos;
	va_start(argumentos,form);
	Log::e(lugarLog,Log::stringConFormato(form,argumentos));
}

void Log::d(LugarLog lugarLog,std::string msj)
{
	Log::log(DEBUG,lugarLog,msj);
}

void Log::e(LugarLog lugarLog,std::string msj)
{
	Log::log(ERROR,lugarLog,msj);
}

/**/



//Private

std::string Log::stringConFormato(char* form,va_list argumentos)
{
char buffer[LOG_MAX_LINE_SIZE];
	std::string bufferString;

	
    vsprintf_s(buffer,LOG_MAX_LINE_SIZE, form,argumentos);
    va_end(argumentos);

	bufferString.assign(buffer);
	return bufferString;
}

std::string Log::logearLugarLog(LugarLog lugarLog)
{
	switch (lugarLog)
	{
		case NO_DEFINIDO:
			return "";
		case PARSER:
			return "[PARSER]";
	}
	return "";
}


std::string Log::logearTipoLog(TipoLog tipoLog)
{
	switch (tipoLog)
	{
		case DEBUG:
			return "[DEBUG]";
		case ERROR :
			return "[ERROR]";
	}
	return "";
}

void Log::log(TipoLog tipoLog,LugarLog lugarLog,std::string msj)
{
	std::ofstream file(LOG_RUTA, std::ios::out | std::ios::app);
	if (file.is_open())
	{
		file	<< Log::logearTipoLog(tipoLog) << " "
				<< Log::logearLugarLog(lugarLog) << " "
				<< Log::tiempoActual() << " " 
				<< msj << "\n";
		file.close();
	}
}


const std::string Log::tiempoActual() {
    time_t now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);

    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

    return buf;
}
