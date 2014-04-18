#pragma once

#ifndef DETECTOR_H_
#define DETECTOR_H_

#include "Event.h"
#include <map>
#include <list>
#include <SDL.h>
#include "Context.h"

using namespace std;
using namespace client_controller_event;


class Detector {
public:
	Detector();
	virtual ~Detector();
	void init();
	void detect();
	void updateStates();
	bool isBeginLife();
	bool isRegenerateWorld();
	bool isPause();
	bool isQuit();


private:




	enum State{QUIT,INITILIZE,REGENERATE,PAUSE,NONE};
	State _state;
	State _previousState;
	map<State, list<Event*>> _mapStateEvent;


	void createStates();
	void createEvents();
	void excecute(SDL_Event* e);


	const Uint8* m_keys;
	void destroyEvents();
	void handleEvents(SDL_Event* e);
};

#endif /* DETECTOR_H_ */
