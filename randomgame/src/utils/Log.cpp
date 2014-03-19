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

void Log::d(std::string msg)
{
	Log::log(DEBUG,msg);
}

void Log::d(char* fmt, ...)
{
	va_list args;
	va_start(args,fmt);
	Log::d(Log::stringWithFormat(fmt,args));
}

void Log::e(std::string msg)
{
	Log::log(ERROR,msg);
}

void Log::e(char* fmt, ...)
{
	va_list args;
	va_start(args,fmt);
	Log::e(Log::stringWithFormat(fmt,args));
}

//Private

std::string Log::stringWithFormat(char* fmt,va_list args)
{
char buffer[LOG_MAX_LINE_SIZE];
	std::string bufferString;

	
    vsprintf_s(buffer,LOG_MAX_LINE_SIZE, fmt,args);
    va_end(args);

	bufferString.assign(buffer);
	return bufferString;
}

std::string Log::typeTextForLogType(LogType logType)
{
	switch (logType)
	{
		case DEBUG:
			return "[DEBUG]";
		case ERROR :
			return "[ERROR]";
	}
	return "";
}

void Log::log(LogType logType,std::string msg)
{
	std::ofstream myfile(LOG_RUTA, std::ios::out | std::ios::app);
	if (myfile.is_open())
	{
		myfile	<< Log::typeTextForLogType(logType) << " "
				<< Log::currentDateTime() << " " 
				<< msg << "\n";
		myfile.close();
	}
}


const std::string Log::currentDateTime() {
    time_t now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);

    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

    return buf;
}
