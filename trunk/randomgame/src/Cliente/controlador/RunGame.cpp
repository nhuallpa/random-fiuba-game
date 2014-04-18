
#include "RunGame.h"
#include "IniGame.h"
#include "StopGame.h"

RunGame* RunGame::runGame = NULL;

void RunGame::handle(Contract* c){
	c->runGame();
}

RunGame* RunGame::getInstance(){
	if(!runGame){
		runGame = new RunGame();
	}
	return runGame;
}

RunGame::RunGame(void){}
RunGame::~RunGame(void){}


State* RunGame::execute(SDL_Event* e, const Uint8* keys){
	State* st = RunGame::getInstance();
	if(keys[SDL_SCANCODE_S]){
		st = IniGame::getInstance();
	}
	else if(keys[SDL_SCANCODE_P]){
		st = StopGame::getInstance();
		st->statePrevious = RunGame::getInstance();
	}
	return st;
}