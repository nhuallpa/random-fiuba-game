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


	Bootstrap bootstrap;
	Activity* currentActivity;
void Cliente::loop(void){
	Log::i("============== INICIANDO CLIENTE =============");		

	Uint32 start = 0;
	bool quit = false;

	bootstrap;
	bootstrap.init();
	GameViewBuilder builder(&this->cLevel);
	currentActivity = new GameActivity(bootstrap.getScreen(), 
													builder, &this->cLevel);
	
	
	/** refresh the initial view*/
	currentActivity->render();

	int running = 0;
	Uint32 tick_inteval = this->getTickInterval();
	next_time = SDL_GetTicks() + tick_inteval;
	bootstrap.getScreen().setState("Juego Creado");
	while (!this->cController.isQuit()){
		cController.handleState(this);
		currentActivity->update();
		currentActivity->render();
		SDL_Delay(time_left());
		next_time += tick_inteval;
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
	//this->cController = GameController(&this->cLevel);
	
	return true;
}


Uint32 Cliente::time_left(void)
{
    Uint32 now;
    now = SDL_GetTicks();
    if (next_time <= now)
        return 0;
    else
        return next_time - now;
}

Uint32 Cliente::getTickInterval()
{
	int fps = 60;
	ParserYaml* aParser = ParserYaml::getInstance();
	fps = Util::string2int(aParser->getInstance()->getEscenarioFps());
	Uint32 tick_interval = 1000.0f / fps;
	return tick_interval;
}




void Cliente::runGame(){
	bootstrap.getScreen().setState("Juego corriendo");
	this->server->getGameEngine().step();
}

void Cliente::stopGame(){
	Log::i("Detencion de secuencia");
	bootstrap.getScreen().setState("Juego Pausado");
}

void Cliente::iniGame(){
	//TODO: Regenerar el mundo
	Log::i("RE-Inicio de secuencia");
	bootstrap.getScreen().setState("Juego Reiniciado");
	this->server->getGameEngine().reInitWorld();
	currentActivity->update();
	currentActivity->render();
}






