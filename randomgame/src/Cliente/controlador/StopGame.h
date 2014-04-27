#ifndef __STOPGAME__
#define __STOPGAME__

#include "Contracts\State.h"

class StopGame : public State{
	public:
		void handle(Contract* c);
		static StopGame* getInstance();
		State* execute(SDL_Event* e, const Uint8* keys);
		void setBind(map<LISTENER, Event>* items){}

	private:
		StopGame(void);
		~StopGame(void);
		static StopGame* stopGame;
};

#endif