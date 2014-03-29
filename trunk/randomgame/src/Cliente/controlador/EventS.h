#pragma once

#ifndef __EVENTS__
#define __EVENTS__

#include "Event.h"

using namespace client_controller_event;

namespace client_controller_events{

	class EventS : public Event
	{
	public:
		static EventS* getInstance();
		void execute(SDL_Event* e, const Uint8* keys);
		bool isBeginLife();
		bool isRegenerateWorld();
		void updateStates();
		static void destroy();
	protected:
		EventS(void);
		~EventS(void);

	private:
		static EventS* _events;
		enum ButtonState{BUTTON_PUSH, BUTTON_POP};
		enum PreviousAction{BEGIN_LIFE, REGENERATE_WORLD};
		ButtonState _buttonState;
		PreviousAction _prevAction;
	};
}
#endif /*__EVENTS__*/
