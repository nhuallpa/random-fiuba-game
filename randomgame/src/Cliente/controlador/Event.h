#pragma once

#ifndef __EVENT__
#define __EVNET__

#include <SDL.h>


namespace client_controller_event{

	class Event
	{
	public:
		Event(void);
		~Event(void);
		virtual void execute(SDL_Event* e, const Uint8* keys);
		virtual void updateStates();
	};
}
#endif /*__EVENT__*/
