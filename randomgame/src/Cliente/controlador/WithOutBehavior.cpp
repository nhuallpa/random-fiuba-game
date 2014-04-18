#include "WithOutBehavior.h"
#include "RunGame.h"
#include "StopGame.h"

WithOutBeHavior* WithOutBeHavior::withOutBeHavior = NULL;

void WithOutBeHavior::handle(Contract* c){
	// without behavior
}

WithOutBeHavior* WithOutBeHavior::getInstance(){
	if(!withOutBeHavior){
		withOutBeHavior = new WithOutBeHavior();
	}
	return withOutBeHavior;
}

WithOutBeHavior::WithOutBeHavior(void){}
WithOutBeHavior::~WithOutBeHavior(void){}


State* WithOutBeHavior::execute(SDL_Event* e, const Uint8* keys){
	State* st = WithOutBeHavior::getInstance();
	if(keys[SDL_SCANCODE_S]){
		st = RunGame::getInstance();
	}
	else if(keys[SDL_SCANCODE_P]){
		st = StopGame::getInstance();
		st->statePrevious = WithOutBeHavior::getInstance();
	}
	return st;
}
