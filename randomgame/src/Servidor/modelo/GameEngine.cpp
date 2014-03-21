#include "GameEngine.h"

GameEngine::GameEngine() {
	
}

GameEngine::~GameEngine() {

}

bool GameEngine::initWorld(){
	return this->gameLevel.createLevel(this->gameLevel);
}



// The engine will loop separately when this runs on different sockets, not now (TP1)
bool GameEngine::loop() {
	//TODO @future
	return true;
}

int GameEngine::howManyPlayers(void){
	//TODO @future - return this->gameLevel.cantidadJugadores();
	return 1;
}

GameLevel GameEngine::getLevel(){

	return this->gameLevel;

}
