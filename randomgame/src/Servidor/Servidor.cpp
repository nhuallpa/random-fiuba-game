#include "Servidor.h"

Servidor::Servidor(void){

}

Servidor::~Servidor(void){

}

bool Servidor::begin(void){

	// TODO @future - Initialize socket

	return true;
}

void Servidor::loop(void){

	// Init conns from clients
	bool quit = false;		
	while (quit == false){
		
		// TODO @future - The engine will loop separately when this runs on different sockets, not now (TP1)
		if( this->gameEngine.initWorld() ) quit = true;
	}

		//TODO @future -  Al finalizar el juego cierro la recepción de jugadores
		return void();
}

bool Servidor::run(void){
	if( this->begin() == true ){
		this->loop();

		//TODO @future - stop receiving data;
	}else{
		//TODO @LOG - "Error al iniciar el juego el cliente.");
		return false;
	}
	return true;
}

void Servidor::destroyWorld(void){
	//TODO @future -  this->gameEngine.destroyWorld();
}

GameLevel Servidor::getLevel(){

	return this->gameEngine.getLevel();
}
