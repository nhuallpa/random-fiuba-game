#pragma once

#include <string>
#include <iostream>

enum LogType{
	DEBUG,
	ERROR
};

class Log
{
public:
	Log(void);
	virtual ~Log(void);
	
	//Debug
	void static d(std::string msg);

	//Esto recibe exactamente lo mismo que printf y sirve para armar errores
	//Maximo LOG_MAX_LINE_SIZE definido en Constantes.h
	void static d(char* fmt, ...);

	//Error
	void static e(std::string msg);

	//Esto recibe exactamente lo mismo que printf y sirve para armar errores
	//Maximo LOG_MAX_LINE_SIZE definido en Constantes.h
	void static e(char* fmt, ...);

private:
	std::string static Log::stringWithFormat(char* fmt,va_list args);
	void static log(LogType logType,std::string msg);
	std::string static typeTextForLogType(LogType logType);
	const static std::string currentDateTime();
};
