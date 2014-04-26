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



void Context::addListener(OnClickListener* c){
	lClistener.push_back(c);
}
void Context::addListener(OnMovementListener* m){
	lMlistener.push_back(m);
}
void Context::addListener(OnScrollListener* s){
	lSlistener.push_back(s);
}
void Context::addListener(OnZoomListener* z){
	lZlistener.push_back(z);
}
void Context::remuveListener(OnClickListener* c){
	list<OnClickListener*>::iterator it;
	list<OnClickListener*>::iterator itDrop;
	it = lClistener.begin();
	itDrop = lClistener.end();
	for(; it != lClistener.end(); it++){
		if((*it) == c){
			itDrop = it;
			break;
		}
	}
	if(itDrop != lClistener.end()){
		lClistener.erase(itDrop);
	}
}
void Context::remuveListener(OnMovementListener* m){
	list<OnMovementListener*>::iterator it;
	list<OnMovementListener*>::iterator itDrop;
	it = lMlistener.begin();
	itDrop = lMlistener.end();
	for(; it != lMlistener.end(); it++){
		if((*it) == m){
			itDrop = it;
			break;
		}
	}
	if(itDrop != lMlistener.end()){
		lMlistener.erase(itDrop);
	}
}
void Context::remuveListener(OnScrollListener* s){
	list<OnScrollListener*>::iterator it;
	list<OnScrollListener*>::iterator itDrop;
	it = lSlistener.begin();
	itDrop = lSlistener.end();
	for(; it != lSlistener.end(); it++){
		if((*it) == s){
			itDrop = it;
			break;
		}
	}
	if(itDrop != lSlistener.end()){
		lSlistener.erase(itDrop);
	}
}
void Context::remuveListener(OnZoomListener* z){
	list<OnZoomListener*>::iterator it;
	list<OnZoomListener*>::iterator itDrop;
	it = lZlistener.begin();
	itDrop = lZlistener.end();
	for(; it != lZlistener.end(); it++){
		if((*it) == z){
			itDrop = it;
			break;
		}
	}
	if(itDrop != lZlistener.end()){
		lZlistener.erase(itDrop);
	}
}

