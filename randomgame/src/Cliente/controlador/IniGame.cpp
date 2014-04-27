
#include "IniGame.h"
#include "RunGame.h"
#include "StopGame.h"

IniGame* IniGame::iniGame = NULL;

void IniGame::handle(Contract* c){
	c->iniGame();
}

IniGame* IniGame::getInstance(){
	if(!iniGame){
		iniGame = new IniGame();
	}
	return iniGame;
}

IniGame::IniGame(void){}
IniGame::~IniGame(void){}

State* IniGame::execute(SDL_Event* e, const Uint8* keys, map<LISTENER,Event> *vec){
	State* st = IniGame::getInstance();
	if(keys[SDL_SCANCODE_S]){
		st = RunGame::getInstance();
	}
	else if(keys[SDL_SCANCODE_P]){
		st = StopGame::getInstance();
		st->statePrevious = IniGame::getInstance();
	}
	return st;
}