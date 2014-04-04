#pragma once
#ifndef __LOG_H_1__
#define __LOG_H_1__
#include <string>
#include <iostream>

enum TipoLog{
	DEBUG,
	ERROR
};

enum LugarLog{
	NO_DEFINIDO,
	PARSER,
	BOOT,
	VIEW_BUILDER
};

class Log
{
public:
	Log(void);
	virtual ~Log(void);
	
	//Debug
	void static d(std::string msj);

	//Esto recibe exactamente lo mismo que printf y sirve para armar errores
	//Maximo LOG_MAX_LINE_SIZE definido en Constantes.h
	void static d(char* form, ...);

	//Error
	void static e(std::string msj);
	//Esto recibe exactamente lo mismo que printf y sirve para armar errores
	//Maximo LOG_MAX_LINE_SIZE definido en Constantes.h
	void static e(char* form, ...);


	/*LOG CON LUGAR*/
	void static Log::d(LugarLog lugarLog,char* form, ...);
	void static Log::e(LugarLog lugarLog,char* form, ...);
	void static Log::d(LugarLog lugarLog,std::string msj);
	void static Log::e(LugarLog lugarLog,std::string msj);

	


private:
	std::string static Log::stringConFormato(char* form,va_list argumentos);
	void static log(TipoLog tipoLog,LugarLog lugarLog,std::string msj);
	std::string static logearTipoLog(TipoLog tipoLog);
	std::string static logearLugarLog(LugarLog lugarLog);
	const static std::string tiempoActual();
};
#endif /**__LOG_H_1__*/