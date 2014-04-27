#ifndef __RUNGAME__
#define __RUNGAME__

#include "Contracts\State.h"
#include "Entity\PartialScreen.h"
#include <vector>

using namespace std;

enum Screen {QUADRANT_1, QUADRANT_2, QUADRANT_3, QUADRANT_4,
			 QUADRANT_5, QUADRANT_6, QUADRANT_7, QUADRANT_8,
			 QUADRANT_9};

class RunGame : public State{
	public:
		void handle(Contract* c);
		static RunGame* getInstance();
		State* execute(SDL_Event* e, const Uint8* keys, map<LISTENER,Event> *vec);

	private:
		RunGame(void);
		~RunGame(void);
		static RunGame* runGame;
		void updateMouse();
		void iniEvent();

		//handle scroll
		map<LISTENER,Event> *items;
		Screen lastScreen;
		PartialScreen* callScreen;
		void detectMouse();
		void loadQuadrantFactory();
		vector<PartialScreen*> screems;
		Side GetCursorLook(int xr, int yr);
};

#endif