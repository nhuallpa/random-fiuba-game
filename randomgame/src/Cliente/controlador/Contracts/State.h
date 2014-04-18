#ifndef __STATE__
#define __STATE__
#include "Contract.h"
#include <cstdlib>
#include <SDL.h>

class State{
	public:
		virtual void handle(Contract* c){}
		virtual State* execute(SDL_Event* e, const Uint8* keys){
			return NULL;
		}
		State* statePrevious;
};

#endif

