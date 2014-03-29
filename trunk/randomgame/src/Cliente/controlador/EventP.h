#pragma once

#ifndef __EVENTP__
#define __EVENTP__

#include "Event.h"
using namespace client_controller_event;

namespace client_controller_eventp{

	class EventP : public Event
	{


	public:
		static EventP* getInstance();
		void execute(SDL_Event* e, const Uint8* keys);
		static void destroy();
		bool isPause();
		void updateStates();
	protected:
		EventP(void);
		~EventP(void);
		bool _pause;

	private:
		static EventP* _eventp;
	};
}
#endif /*__EVENTP__*/

	