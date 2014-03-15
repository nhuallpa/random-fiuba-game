#include "./Cliente.h"
#include <string>
#include <iostream>
#include <ctime>

Cliente::Cliente(Servidor* server){
	this->server = server;
}

Cliente::~Cliente(void){

}

bool Cliente::begin(){
	// TODO @future: Initialize sockets
	this->connect2server(this->server);
	return true;
}

void Cliente::loop(void){

	bool quit = false;

	//init View
	this->cView.init();

	//init Controller
	this->cController.init();

	while (quit == false){

		this->cController.detectEvents();
		this->cController.handleEvents();

		this->cView.clearScreen();
		this->cView.render();

	}
}

bool Cliente::run(){

	if( this->begin() == true ){
		this->loop();
	}else{
		//TODO: LOG - "Error al iniciar el juego el cliente.");
		return false;
	}
	return true;
}

void Cliente::destroyWorld(void){
	//TODO: Destructor
}




bool Cliente::connect2server(Servidor* server){
	this->cLevel = server->getLevel();
	this->cController = GameController(&this->cLevel,&this->cView);
	return true;
}








