#ifndef __WITHOUTBEHAV__
#define __WITHOUTBEHAV__

#include "Contracts\State.h"

class WithOutBeHavior : public State{
	public:
		void handle(Contract* c);
		static WithOutBeHavior* getInstance();
		State* execute(SDL_Event* e, const Uint8* keys);
	private:
		WithOutBeHavior(void);
		~WithOutBeHavior(void);
		static WithOutBeHavior* withOutBeHavior;
};

#endif