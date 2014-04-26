#pragma once

#ifndef __CONTEXT__
#define __CONTEXT__

#include "Contracts\State.h"
#include "Contracts\Contract.h"
#include "Contracts\OnClickListener.h"
#include "Contracts\OnMovementListener.h"
#include "Contracts\OnScrollListener.h"
#include "Contracts\OnZoomListener.h"
#include <SDL.h>
#include <list>
#include <map>
#include "Entity\Event.h"

using namespace std;

class Context{
	public:
		Context(void);
		~Context(void);
		void request(Contract* c);
		bool isQuit();
		void addListener(OnClickListener* c);
		void addListener(OnMovementListener* m);
		void addListener(OnScrollListener* s);
		void addListener(OnZoomListener* z);
		void remuveListener(OnClickListener* c);
		void remuveListener(OnMovementListener* m);
		void remuveListener(OnScrollListener* s);
		void remuveListener(OnZoomListener* z);
	private:
		list<OnClickListener*> lClistener;
		list<OnMovementListener*> lMlistener;
		list<OnScrollListener*> lSlistener;
		list<OnZoomListener*> lZlistener;
		const Uint8* m_keys;
		bool quit;
		State* state;
		void handleEvents(SDL_Event* e);
		void detect();
		bool isValidKey(SDL_Event* e);
		enum LISTENER{CL, ML, SL, ZL};
		map<LISTENER, Event> items;


		
		void notifier(pair<LISTENER, Event> item);
		void notifierC(Event e);
		void notifierM(Event e);
		void notifierS(Event e);
		void notifierZ(Event e);

};

#endif /*__CONTEXT__*/

	