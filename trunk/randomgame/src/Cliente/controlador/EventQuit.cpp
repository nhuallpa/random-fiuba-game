#include "EventQuit.h"

using namespace std;
using namespace client_controller_eventquit;


EventQuit* EventQuit::_eventquit = NULL;



EventQuit::EventQuit(void)
{
	_quit = false;
}

EventQuit::~EventQuit(void){}




void EventQuit::execute(SDL_Event* e, const Uint8* keys){
	if(e->type == SDL_QUIT){
		_quit = true;
	}
}

bool EventQuit::isQuit(){
	return _quit;
}

void EventQuit::updateStates(){
	return;
}

EventQuit* EventQuit::getInstance(){

	if(!_eventquit){
		_eventquit = new EventQuit();
	}
	return _eventquit;
}


void EventQuit::destroy(){
	if(_eventquit){
		delete _eventquit;
		_eventquit = NULL;
	}
}

