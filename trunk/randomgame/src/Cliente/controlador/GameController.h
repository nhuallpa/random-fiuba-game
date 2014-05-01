#pragma once

#ifndef GAMECONTROLLER_H_
#define GAMECONTROLLER_H_

#include "RunGame.h"
#include "Contracts\OnClickListener.h"
#include "Contracts\OnMovementListener.h"
#include "Contracts\OnScrollListener.h"
#include "Contracts\OnZoomListener.h"
#include <SDL.h>
#include <list>
#include <map>
#include "Entity\Event.h"


using namespace std;



class GameController{
	public:
		GameController(void);
		~GameController(void);
		void handleState(Contract* c);
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
		//list<OnClickListener*> lClistener;
		list<OnMovementListener*> lMlistener;
		//list<OnScrollListener*> lSlistener;
		//list<OnZoomListener*> lZlistener;
		const Uint8* m_keys;
		bool quit;
		RunGame* rg;
		void handleEvents(SDL_Event* e);
		void detect();
		bool isValidKey(SDL_Event* e);
		map<LISTENER, Event> items;
		

		void call();
		void notifier(pair<LISTENER, Event> item);
		//void notifierC(Event e);
		void notifierM(Event e);
		//void notifierS(Event e);
		//void notifierZ(Event e);

};

#endif 


/*
#pragma once

#ifndef GAMECONTROLLER_H_
#define GAMECONTROLLER_H_

#include "Contracts\Contract.h"
#include "Context.h"

class GameController {
public:
	void handleState(Contract* c);
	bool isQuit();
	GameController();
	~GameController();
	void addListener(OnClickListener* c);
	void addListener(OnMovementListener* m);
	void addListener(OnScrollListener* s);
	void addListener(OnZoomListener* z);
	void remuveListener(OnClickListener* c);
	void remuveListener(OnMovementListener* m);
	void remuveListener(OnScrollListener* s);
	void remuveListener(OnZoomListener* z);
private:
	Context ctx;

};

#endif // GAMECONTROLLER_H_ 
*/