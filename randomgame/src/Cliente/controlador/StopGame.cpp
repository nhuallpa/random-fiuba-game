#include "StopGame.h"
#include "RunGame.h"
#include "IniGame.h"


StopGame* StopGame::stopGame = NULL;

void StopGame::handle(Contract* c){
	c->stopGame();
}

StopGame* StopGame::getInstance(){
	if(!stopGame){
		stopGame = new StopGame();
	}
	return stopGame;
}

StopGame::StopGame(void){}
StopGame::~StopGame(void){}


State* StopGame::execute(SDL_Event* e, const Uint8* keys){
	State* st = StopGame::getInstance();
	if(keys[SDL_SCANCODE_S]){
		//TODO: ACA DEBERIA REINICIAR
	}
	else if(keys[SDL_SCANCODE_P]){
		st = this->statePrevious;
	}
	return st;
}
