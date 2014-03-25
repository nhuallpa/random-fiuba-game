#include "./Cliente.h"
#include "../utils/Log.h"
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
	std::cout << "antes de view init" << std::endl;
	this->cView.init();
	std::cout << "despues de view init" << std::endl;
	//init Controller
	this->cController.init();

	while (quit == false){

		this->cController.detectEvents();
		quit = this->cController.handleEvents();

		this->cView.clearScreen();
		this->cView.render();

	}
}

bool Cliente::run(){

	if( this->begin() == true ){
		this->loop();
	}else{
		Log::e("Error al iniciar el juego el cliente");
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








