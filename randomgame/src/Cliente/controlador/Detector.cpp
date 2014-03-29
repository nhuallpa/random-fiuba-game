#include "Detector.h"
#include "../../utils/Log.h"
#include "EventS.h"
#include "EventP.h"
#include "EventQuit.h"

using namespace std;
using namespace client_controller_events;
using namespace client_controller_eventp;
using namespace client_controller_eventquit;


Detector::Detector() {
	m_keys = SDL_GetKeyboardState(NULL);
}

Detector::~Detector() {
	destroyEvents();
}

void Detector::init(){
	_state = REGENERATE;
	_previousState = REGENERATE;
	createStates();
	createEvents();
}

void Detector::detect(){
	SDL_Event* ev = new SDL_Event();
	SDL_StartTextInput();
	while(SDL_PollEvent( ev ))
	{
		this->handleEvents(ev);
	}
	delete ev;
}

void Detector::createStates(){
	_mapStateEvent.insert(pair<State, list<Event*>>(INITILIZE,NULL));
	_mapStateEvent.insert(pair<State, list<Event*>>(REGENERATE,NULL));
	_mapStateEvent.insert(pair<State, list<Event*>>(PAUSE,NULL));
}

void Detector::createEvents(){
	//Events for initialize
	list<Event*> listInit;
	listInit.push_back(EventS::getInstance());
	listInit.push_back(EventP::getInstance());
	listInit.push_back(EventQuit::getInstance());
	_mapStateEvent[INITILIZE] = listInit;

	//Events for regenerate
	_mapStateEvent[REGENERATE] = listInit;

	//Events for pause
	list<Event*> listInit2;
	listInit2.push_back(EventQuit::getInstance());
	listInit2.push_back(EventP::getInstance());
	_mapStateEvent[PAUSE] = listInit2;
}


void Detector::destroyEvents(){
	EventS* elementS = EventS::getInstance();
	EventP* elementP = EventP::getInstance();
	EventQuit* elementQ = EventQuit::getInstance();
	elementS->destroy();
	elementP->destroy();
	elementQ->destroy();
}

void Detector::excecute(SDL_Event* e){
	list<Event*>::iterator it;
	for(it = _mapStateEvent[_state].begin();
		it != _mapStateEvent[_state].end(); 
		it++){
		(*it)->execute(e, m_keys);
	}
}

void Detector::handleEvents(SDL_Event* e){
	SDL_PumpEvents();
	if(e->type == SDL_KEYDOWN || e->type == SDL_QUIT){
		excecute(e);
	}
}

bool Detector::isBeginLife(){
	EventS* element = EventS::getInstance();
	return element->isBeginLife();
}

bool Detector::isRegenerateWorld(){
	EventS* element = EventS::getInstance();
	return element->isRegenerateWorld();
}

bool Detector::isPause(){
	EventP* element = EventP::getInstance();
	return element->isPause();
}

bool Detector::isQuit(){
	EventQuit* element = EventQuit::getInstance();
	return element->isQuit();
}


void Detector::updateStates(){
	list<Event*>::iterator it;
	if(isBeginLife()){
		_previousState = _state;
		_state = INITILIZE;
	}
	else if(isRegenerateWorld()){
		_previousState = _state;
		_state = REGENERATE;
	}
	else if(isQuit()){
		_previousState = _state;
		_state = QUIT;
	}
	else if(isPause() && _state != PAUSE){
		_previousState = _state;
		_state = PAUSE;
	}
	else if(!isPause() && _state == PAUSE){
		_state = _previousState;
		_previousState = PAUSE;
	}
	for(it = _mapStateEvent[_state].begin();
		it != _mapStateEvent[_state].end(); 
		it++){
			(*it)->updateStates();
	}
}



