
#include "RunGame.h"
#include "IniGame.h"
#include "StopGame.h"

RunGame* RunGame::runGame = NULL;

RunGame::RunGame(void){}

RunGame::~RunGame(void){}

void RunGame::handle(Contract* c){
	c->runGame();
	this->updateMouse();
}

RunGame* RunGame::getInstance(){
	if(!runGame){
		runGame = new RunGame();
	}
	return runGame;
}


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


void RunGame::updateMouse(){
	Uint32 button;
	SDL_PumpEvents();
	int x, y;
	button = SDL_GetMouseState(&x, &y);
	/*if((button & SDL_BUTTON(1)) == 1){
		x = y;
	}*/  //SDL_BUTTON_LEFT 1
	if((button & SDL_BUTTON(2)) == 1) {
		x = y;
	}//SDL_BUTTON_MIDDLE 2
	if((button & SDL_BUTTON(3)) == 1) {
		x = y;
	}//SDL_BUTTON_RIGHT 3
	if((button & SDL_BUTTON(4)) == 1) {
		x = y;
	}//SDL_BUTTON_WHEELUP 4
	if((button & SDL_BUTTON(5)) == 1) {
		x = y;
	}//SDL_BUTTON_WHEELDOWN 5
}

