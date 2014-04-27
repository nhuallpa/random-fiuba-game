#ifndef __STATE__
#define __STATE__

#include "Contract.h"
#include <cstdlib>
#include <SDL.h>
#include "..\Entity\Event.h"
#include <map>

using namespace std;

enum LISTENER{CL, ML, SL, ZL};

class State{
	public:
		virtual void setBind(map<LISTENER, Event>* items){}
		virtual void handle(Contract* c){}
		virtual State* execute(SDL_Event* e, const Uint8* keys){
			return NULL;
		}
		State* statePrevious;
};

#endif

