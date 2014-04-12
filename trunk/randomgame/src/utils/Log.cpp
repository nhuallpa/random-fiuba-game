#include "Log.h"


Log::Log(void)
{
	retriveConfigFile();
	file.open(this->properties["log.file"].c_str(), std::ios::trunc);
}

Log::~Log(void)
{
	if (file.is_open())
	{
		file.close();
	}
}

void Log::retriveConfigFile()
{
	properties = Util::loadProperteries(LOG_CONFIG_FILE);
	if (this->properties.size() == 0)
	{
		this->properties["log.file"] = "./DI_Log.txt";	
		this->properties["log.maxline"] = "256";	
		this->properties["log.level"] = "2";	
	}
}

void Log::t(char* form, ...)
{
	va_list argumentos;
	va_start(argumentos,form);
	Log::t(Log::Instance().stringConFormato(form,argumentos));
}

void Log::d(char* form, ...)
{
	va_list argumentos;
	va_start(argumentos,form);
	Log::d(Log::Instance().stringConFormato(form,argumentos));
}

void Log::i(char* form, ...)
{
	va_list argumentos;
	va_start(argumentos,form);
	Log::i(Log::Instance().stringConFormato(form,argumentos));
}

void Log::e(char* form, ...)
{
	va_list argumentos;
	va_start(argumentos,form);
	Log::e(Log::Instance().stringConFormato(form,argumentos));
}

/** ================================== */

void Log::t(std::string msj)
{
	Log::Instance().log(TRACE, NO_DEFINIDO, msj);
}

void Log::d(std::string msj)
{
	Log::Instance().log(DEBUG, NO_DEFINIDO, msj);
}

void Log::i(std::string msj)
{
	Log::Instance().log(INFO, NO_DEFINIDO, msj);
}

void Log::e(std::string msj)
{
	Log::Instance().log(ERROR, NO_DEFINIDO, msj);
}

/** ================================== */


void Log::t(LugarLog lugarLog,char* form, ...)
{
	va_list argumentos;
	va_start(argumentos,form);
	Log::Instance().log(TRACE,
						lugarLog, 
						Log::Instance().stringConFormato(form,argumentos));
}


void Log::d(LugarLog lugarLog,char* form, ...)
{
	va_list argumentos;
	va_start(argumentos,form);
	Log::Instance().log(DEBUG,
						lugarLog, 
						Log::Instance().stringConFormato(form,argumentos));
}


void Log::i(LugarLog lugarLog,char* form, ...)
{
	va_list argumentos;
	va_start(argumentos,form);
	Log::Instance().log(INFO,
						lugarLog,
						Log::Instance().stringConFormato(form,argumentos));
}


void Log::e(LugarLog lugarLog,char* form, ...)
{
	va_list argumentos;
	va_start(argumentos,form);
	Log::Instance().log(ERROR,
						lugarLog,
						Log::Instance().stringConFormato(form,argumentos));
}

/** ================================== */

void Log::t(LugarLog lugarLog,std::string msj)
{
	Log::Instance().log(TRACE, 
						lugarLog, 
						msj);
}

void Log::d(LugarLog lugarLog,std::string msj)
{
	Log::Instance().log(DEBUG, 
						lugarLog, 
						msj);
}

void Log::i(LugarLog lugarLog,std::string msj)
{
	Log::Instance().log(INFO,
						lugarLog, 
						msj);
}

void Log::e(LugarLog lugarLog,std::string msj)
{
	Log::Instance().log(ERROR,
						lugarLog, 
						msj);
}

/**/


void Log::log(TipoLog tipoLog, LugarLog lugarLog, std::string msj)
{
	int level = (Util::esUnsInt(this->properties["log.level"]))? 
								Util::string2int(this->properties["log.level"]):
										LOG_LEVEL;

	if (file.is_open() && tipoLog >= level)
	{
		file	<< Log::tiempoActual() << " " 
				<< Log::logearTipoLog(tipoLog) << " "
				<< Log::logearLugarLog(lugarLog) << " "
				<< msj << "\n";

		file.flush();
	}
}

std::string Log::logearTipoLog(TipoLog tipoLog)
{
	switch (tipoLog)
	{
		case TRACE:
			return "[TRACE]";
			break;
		case DEBUG:
			return "[DEBUG]";
			break;
		case INFO :
			return "[INFO] ";
			break;
		case ERROR :
			return "[ERROR]";
	}
	return "";
}


std::string Log::logearLugarLog(LugarLog lugarLog)
{
	switch (lugarLog)
	{
		case NO_DEFINIDO:
			return "";
		case PARSER:
			return "[PARSER]";
		case VIEW:
			return "[VISTA]";
	}
	return "";
}


const std::string Log::tiempoActual() {
    time_t now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);

    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

    return buf;
}



std::string Log::stringConFormato(char* form,va_list argumentos)
{
	int max_line = (Util::esUnsInt(this->properties["log.maxline"]))? 
								Util::string2int(this->properties["log.maxline"]):
										LOG_MAX_LINE_SIZE;

	char* buffer = new char[max_line];
	std::string bufferString;

    vsprintf_s(buffer, max_line, form,argumentos);
    va_end(argumentos);

	bufferString.assign(buffer);
	delete buffer;
	return bufferString;
}

