#ifndef __INIGAME__
#define __INIGAME__

#include "Contracts\State.h"

class IniGame : public State{
	public:
		void handle(Contract* c);
		static IniGame* getInstance();
		State* execute(SDL_Event* e, const Uint8* keys);
		void setBind(map<LISTENER, Event>* items){}

	private:
		IniGame(void);
		~IniGame(void);
		static IniGame* iniGame;
};

#endif