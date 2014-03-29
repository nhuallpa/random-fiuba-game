#pragma once

#ifndef __EVENTQUIT__
#define __EVENTQUIT__

#include "Event.h"

using namespace client_controller_event;

namespace client_controller_eventquit{

	class EventQuit : public Event
	{
	public:
		static EventQuit* getInstance();
		void execute(SDL_Event* e, const Uint8* keys);
		static void destroy();
		bool isQuit();
		void updateStates();
	protected:
		EventQuit(void);
		~EventQuit(void);
		bool _quit;
	private:
		static EventQuit* _eventquit;
	};
}
#endif /*__EVENTQUIT__*/
