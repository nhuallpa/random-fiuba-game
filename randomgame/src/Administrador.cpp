#include "./Administrador.h"
#include <string>
#include <iostream>

Administrador::Administrador(void){
	this->isServer = false;
	this->aServer = NULL;
	this->aClient = NULL;
}

Administrador::~Administrador(void){
	if( this->aServer != NULL){
		this->aServer->destroyWorld();
		delete this->aServer;
		this->aServer = NULL;
	}

	if( this->aClient != NULL){
		this->aClient->destroyWorld();
		delete this->aClient;
		this->aClient = NULL;
	}
}

void Administrador::run(){

	this->parseCommands();

	this->aServer = new Servidor();
	if( this->aServer->run() == false ){
			std::cout << "error" << std::endl;
			//TODO @LOG - "Error al correr el juego en modo Servidor";
		}
	
	this->aClient = new Cliente(this->aServer);
	if( this->aClient->run() == false ){
		std::cout << "error" << std::endl;
		//TODO @LOG - "Error al correr el juego en modo Cliente";
	}	
	return void();
}

void Administrador::parseCommands(void){

	// TODO @future - Detects if it's going to run as server or client mode
	return void();
}
