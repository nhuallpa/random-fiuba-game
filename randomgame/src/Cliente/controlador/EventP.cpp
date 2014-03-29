#include "EventP.h"

using namespace std;
using namespace client_controller_eventp;


EventP* EventP::_eventp = NULL;

EventP::EventP(void)
{
	_pause = false;
}

EventP::~EventP(void){}

EventP* EventP::getInstance(){
	if(!_eventp){
		_eventp = new EventP();
	}
	return _eventp;
}


void EventP::execute(SDL_Event* e, const Uint8* keys){
	if(keys[SDL_SCANCODE_P]){
		if(!_pause){
			_pause = true;
		}
		else{
			_pause = false;
		}
	}
}

bool EventP::isPause(){
	return _pause;
}

void EventP::updateStates(){
	return;
}

void EventP::destroy(){
	if(_eventp){
		delete _eventp;
		_eventp = NULL;
	}
}

