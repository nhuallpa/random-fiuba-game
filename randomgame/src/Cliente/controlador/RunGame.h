#ifndef __RUNGAME__
#define __RUNGAME__
#include <SDL.h>
#include "Entity\PartialScreen.h"
#include "../../utils/Log.h"
#include <vector>
#include "Entity\Over.h"
#include "Entity\Click.h"
#include "Entity\Zoom.h"
#include "Entity\Move.h"
#include "Contracts\Notifiable.h"

using namespace std;

enum Screen {QUADRANT_1, QUADRANT_2, QUADRANT_3, QUADRANT_4,
			 QUADRANT_5, QUADRANT_6, QUADRANT_7, QUADRANT_8,
			 QUADRANT_9};

class RunGame{
	public:
		void handle();
		static RunGame* getInstance();
		void execute(SDL_Event* e, const Uint8* keys);
		void call();

	private:
		RunGame(void);
		~RunGame(void);
		static RunGame* runGame;
		void updateMouse();
		void iniEvent();

		//handle scroll
		PartialScreen* callScreen;
		void detectMouse();
		void loadQuadrantFactory();
		vector<PartialScreen*> screems;
		Side GetCursorLook(int xr, int yr);


		//handle wheel
		SDL_MouseWheelEvent wheel;
		void detectWheel();

		//handle click
		void detectClick();

		//handle Movement
		void detectMovem(SDL_Event* e);

		int WIDTH, HIGHT;
		
		list<Notifiable*> l;
};

#endif