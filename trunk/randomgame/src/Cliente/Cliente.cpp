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

	/** Retrieve the domain element to create the view elements*/
	std::map<int,GameElement> map = this->cLevel.getModelElements();
	GameViewBuilder builder(map);

	Activity* currentActivity = new GameActivity(bootstrap.getScreen(), builder);

	// @Nestor, esto te devuelve todos los GameElements en un map que tiene de clave id
	// A esos gameElement le podes pedir los vertices, pos (te da la central), height, width,
	// angle, mass, etc. Usalo para dibujar inicialmente en el build y dentro de cada update.
	

	//a cada element hacele getVertex() que te devuelve una lista de pair<int,int> cada pos
	// del par (x,y) la multiplicas por la conversion a pixels y listo
	


	this->cController.init();


	int running = 0;
	while (!this->cController.isQuit()){
		
		this->cController.detectEvents();
		this->cController.handleEvents();

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
		if(this->cController.isPause()){
			running=0;
			//TODO: Parar el mundo en el estado en el que esta!!!
		}

		if (running){
			this->server->getGameEngine().step();
			currentActivity->update();
			currentActivity->render();
		}

		/*currentActivity->update();
		currentActivity->render();
		*/
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
	//this->cController = GameController(&this->cLevel,&this->cView);
	this->cController = GameController(&this->cLevel);
	return true;
}








