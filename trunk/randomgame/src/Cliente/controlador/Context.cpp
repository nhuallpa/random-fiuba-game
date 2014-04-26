#include "Context.h"
#include "WithOutBehavior.h"

Context::Context(){
	m_keys = SDL_GetKeyboardState(NULL);
	quit = false;
	state = WithOutBeHavior::getInstance();
}
Context::~Context(){}
void Context::request(Contract* c){
	detect();
	state->handle(c);
}

void Context::detect(){
	SDL_Event* ev = new SDL_Event();
	SDL_StartTextInput();
	while(SDL_PollEvent( ev ))
	{
		this->handleEvents(ev);
	}
	delete ev;
}

void Context::handleEvents(SDL_Event* e){
	SDL_PumpEvents();
	if(this->isValidKey(e)){
		state = state->execute(e, m_keys);
	}
	else if(e->type == SDL_QUIT){
		quit = true;
	}
}

bool Context::isQuit(){
	return quit;
}


bool Context::isValidKey(SDL_Event* e){
	return ((e->type == SDL_KEYDOWN) 
		||  (e->type == SDL_KEYUP));
}

