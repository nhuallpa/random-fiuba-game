#pragma once

#ifndef __CONTEXT__
#define __CONTEXT__

#include "Contracts\State.h"
#include "Contracts\Contract.h"
#include <SDL.h>

class Context{
	public:
		Context(void);
		~Context(void);
		void request(Contract* c);
		bool isQuit();
	private:
		const Uint8* m_keys;
		bool quit;
		State* state;
		void handleEvents(SDL_Event* e);
		void detect();
		bool isValidKey(SDL_Event* e);
};

#endif /*__CONTEXT__*/

	