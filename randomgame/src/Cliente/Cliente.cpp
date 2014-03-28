#include "./Cliente.h"
#include "../utils/Log.h"
#include <string>
#include <iostream>
#include <ctime>
#include "vista\Bootstrap.h"
#include "vista\Activity.h"
#include "vista\GameActivity.h"

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

	Bootstrap bootstrap;
	bootstrap.init();

	Activity* currentActivity = new GameActivity(bootstrap.getScreen());

	//init View
	//this->cView.init();

	//init Controller
	this->cController.init();
	int running = 0;
	while (quit == false){
		
		this->cController.detectEvents();
		quit = this->cController.handleEvents();

		if(this->cController.isBeginLife()){
			running=1;
			//TODO: Darle vida al mundo
		}
		if(this->cController.isRegenerateWorld()){
			//TODO: Regenerar el mundo
			this->server->getGameEngine().reInitWorld();
			currentActivity->update();
			currentActivity->render();
			running = 0;
		}
		if(this->cController.isPuase()){
			running=0;
			//TODO: Parar el mundo en el estado en el que esta!!!
			//this->cController.detectEvents();
		}

		if (running){
			this->server->getGameEngine().step();
			currentActivity->update();
			currentActivity->render();
		}

		this->cController.clearStates();
	}
	bootstrap.getScreen().terminate();
	delete currentActivity;

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








