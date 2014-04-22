#ifndef __RUNGAME__
#define __RUNGAME__

#include "Contracts\State.h"

class RunGame : public State{
	public:
		void handle(Contract* c);
		static RunGame* getInstance();
		State* execute(SDL_Event* e, const Uint8* keys);

	private:
		RunGame(void);
		~RunGame(void);
		static RunGame* runGame;
		void updateMouse();
};

#endif