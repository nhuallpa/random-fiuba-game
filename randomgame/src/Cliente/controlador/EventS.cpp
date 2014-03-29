#include "EventS.h"

using namespace std;
using namespace client_controller_events;

EventS* EventS::_events = NULL;


EventS::EventS(void)
{
	_buttonState = BUTTON_POP;
	_prevAction = REGENERATE_WORLD;
}


EventS::~EventS(void){}

EventS* EventS::getInstance(){
	if(!_events){
		_events = new EventS();
	}
	return _events;
}

void EventS::execute(SDL_Event* e, const Uint8* keys){
	if(keys[SDL_SCANCODE_S]){
		_buttonState = BUTTON_PUSH;
	}
	else{
		_buttonState = BUTTON_POP;
	}
	return;
}

bool EventS::isBeginLife(){
	return  ((_prevAction == REGENERATE_WORLD)
		  && (_buttonState == BUTTON_PUSH));
}

bool EventS::isRegenerateWorld(){
	return  ((_prevAction == BEGIN_LIFE)
		  && (_buttonState == BUTTON_PUSH));
}

void EventS::updateStates(){
	if(_buttonState == BUTTON_PUSH){	
		if(_prevAction == REGENERATE_WORLD){
			_prevAction = BEGIN_LIFE;
		}
		else{
			_prevAction = REGENERATE_WORLD;
		}
	}
	_buttonState = BUTTON_POP;
}

void EventS::destroy(){
	if(_events){
		delete _events;
		_events = NULL;
	}
}


