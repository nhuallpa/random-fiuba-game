
#include "RunGame.h"
#include "IniGame.h"
#include "StopGame.h"

#define DELTA 40
#define WIDTH 400
#define HIGHT 400

RunGame* RunGame::runGame = NULL;

RunGame::RunGame(void){
	this->lastScreen = QUADRANT_9;
	this->loadQuadrantFactory();
	callScreen = new PartialScreen();
	callScreen->id = QUADRANT_9;
}

RunGame::~RunGame(void){}

void RunGame::handle(Contract* c){
	c->runGame();
	SDL_PumpEvents();
	this->detectMouse();
	this->iniEvent();
}

void RunGame::iniEvent(){
	Event e;
	//scroll
	if(lastScreen != callScreen->id){
		//cambio a otro evento
		lastScreen = (Screen) callScreen->id;
		e.value = lastScreen;
		items->insert(pair<LISTENER, Event>(SL, e));
	}

}

RunGame* RunGame::getInstance(){
	if(!runGame){
		runGame = new RunGame();
	}
	return runGame;
}


State* RunGame::execute(SDL_Event* e, const Uint8* keys, map<LISTENER,Event> *vec){
	State* st = RunGame::getInstance();
	this->items = vec;

	wheel = e->wheel;
	this->detectWheel();
	/*this->detectClick();*/

	if(keys[SDL_SCANCODE_S]){
		st = IniGame::getInstance();
	}
	else if(keys[SDL_SCANCODE_P]){
		st = StopGame::getInstance();
		st->statePrevious = RunGame::getInstance();
	}
	return st;
}

Side RunGame::GetCursorLook(int xr, int yr){
	if(xr >= 0)
		return S_RIGHT;
	else if(xr < 0)
		return S_LEFT;
	else if(yr >= 0)
		return S_DOWN;
	else
		return S_UP;
}

void RunGame::detectWheel(){
	map<LISTENER,Event>::iterator it;
	Event e;

	it = items->find(ZL);
	if(it == items->end()){
		if(this->wheel.type == SDL_MOUSEWHEEL){
			e.y = this->wheel.y;
			if(this->wheel.y > 0){
				e.value = 0;
				items->insert(pair<LISTENER, Event>(ZL, e));
			}
			else{
				e.value = 1;
				items->insert(pair<LISTENER, Event>(ZL, e));
			}
		}
	}

}

void RunGame::detectClick(){
	map<LISTENER,Event>::iterator it;
	Event e;

	it = items->find(CL);
	if(it == items->end()){
		int x, y = 0;
		Uint32 button = SDL_GetMouseState(&x, &y);
		if(button & SDL_BUTTON(1)){
			e.x = x, e.y = y, e.value = 0;
			items->insert(pair<LISTENER,Event>(CL, e));
		} 

	}

}

void RunGame::detectMouse(){
	vector<PartialScreen*>::iterator it;
	PartialScreen* result = NULL;
	Side s;
	int x, y, xr, yr;
	SDL_GetMouseState(&x, &y);
	SDL_GetRelativeMouseState(&xr, &yr);
	s = this->GetCursorLook(xr, yr);
	for(it = this->screems.begin();
		it != this->screems.end();
		it++){
			result = (*it)->Inside(x, y, s);
			if(result != NULL){
				callScreen = result;
				break;
			}
	}
	if(result == NULL){
		//callScreen = result;
	}
}

void RunGame::loadQuadrantFactory(){
	PartialScreen* s1 = new PartialScreen();
	PartialScreen* s2 = new PartialScreen();
	PartialScreen* s3 = new PartialScreen();
	PartialScreen* s4 = new PartialScreen();
	PartialScreen* s5 = new PartialScreen();
	PartialScreen* s6 = new PartialScreen();
	PartialScreen* s7 = new PartialScreen();
	PartialScreen* s8 = new PartialScreen();
	PartialScreen* s9 = new PartialScreen();

	//seteo id
	s1->id = QUADRANT_1, s2->id = QUADRANT_2;
	s3->id = QUADRANT_3, s4->id = QUADRANT_4;
	s5->id = QUADRANT_5, s6->id = QUADRANT_6;
	s7->id = QUADRANT_7, s8->id = QUADRANT_8;
	s9->id = QUADRANT_9;

	//seteo rangos
	s1->xFrom = 0, s1->xTo = DELTA, s1->yFrom = 0, s1->yTo = DELTA;
	s2->xFrom = WIDTH - DELTA, s2->xTo = WIDTH, s2->yFrom = 0, s2->yTo = DELTA;
	s3->xFrom = 0, s3->xTo = DELTA, s3->yFrom = HIGHT - DELTA, s3->yTo = HIGHT;
	s4->xFrom = WIDTH - DELTA, s4->xTo = WIDTH, s4->yFrom = HIGHT - DELTA, s4->yTo = HIGHT;
	s5->xFrom = DELTA, s5->xTo = WIDTH - DELTA, s5->yFrom = 0, s5->yTo = DELTA;
	s6->xFrom = DELTA, s6->xTo = WIDTH - DELTA, s6->yFrom = HIGHT - DELTA, s6->yTo = HIGHT;
	s7->xFrom = 0, s7->xTo = DELTA, s7->yFrom = DELTA, s7->yTo = HIGHT - DELTA;
	s8->xFrom = WIDTH - DELTA, s8->xTo = WIDTH, s8->yFrom = DELTA, s8->yTo = HIGHT - DELTA;
	s9->xFrom = DELTA, s9->xTo = WIDTH - DELTA, s9->yFrom = DELTA, s9->yTo = HIGHT - DELTA;

	//Seteo relaciones
	s1->dir.insert(pair<int, Side>(QUADRANT_5, S_RIGHT));
	s1->dir.insert(pair<int, Side>(QUADRANT_7, S_DOWN));
	s1->addRelationScreen(s5), s1->addRelationScreen(s7);

	s2->dir.insert(pair<int, Side>(QUADRANT_5, S_LEFT));
	s2->dir.insert(pair<int, Side>(QUADRANT_8, S_DOWN));
	s2->addRelationScreen(s5), s2->addRelationScreen(s8);

	s3->dir.insert(pair<int, Side>(QUADRANT_6, S_RIGHT));
	s3->dir.insert(pair<int, Side>(QUADRANT_7, S_UP));
	s3->addRelationScreen(s6), s3->addRelationScreen(s7);

	s4->dir.insert(pair<int, Side>(QUADRANT_6, S_LEFT));
	s4->dir.insert(pair<int, Side>(QUADRANT_8, S_UP));
	s4->addRelationScreen(s6), s4->addRelationScreen(s8);

	s5->dir.insert(pair<int, Side>(QUADRANT_1, S_LEFT));
	s5->dir.insert(pair<int, Side>(QUADRANT_2, S_RIGHT));
	s5->addRelationScreen(s1), s5->addRelationScreen(s2);

	s6->dir.insert(pair<int, Side>(QUADRANT_3, S_LEFT));
	s6->dir.insert(pair<int, Side>(QUADRANT_4, S_RIGHT));
	s6->addRelationScreen(s3), s6->addRelationScreen(s4);

	s7->dir.insert(pair<int, Side>(QUADRANT_1, S_UP));
	s7->dir.insert(pair<int, Side>(QUADRANT_3, S_DOWN));
	s7->addRelationScreen(s1), s7->addRelationScreen(s3);

	s8->dir.insert(pair<int, Side>(QUADRANT_2, S_UP));
	s8->dir.insert(pair<int, Side>(QUADRANT_4, S_DOWN));
	s8->addRelationScreen(s2), s8->addRelationScreen(s4);

	s9->dir.insert(pair<int, Side>(QUADRANT_5, S_UP));
	s9->dir.insert(pair<int, Side>(QUADRANT_6, S_DOWN));
	s9->dir.insert(pair<int, Side>(QUADRANT_7, S_LEFT));
	s9->dir.insert(pair<int, Side>(QUADRANT_8, S_RIGHT));
	s9->addRelationScreen(s5), s9->addRelationScreen(s6);
	s9->addRelationScreen(s7), s9->addRelationScreen(s8);

	//Los agrego para luego recorrerlos
	screems.push_back(s1), screems.push_back(s2);
	screems.push_back(s3), screems.push_back(s4);
	screems.push_back(s5), screems.push_back(s6);
	screems.push_back(s7), screems.push_back(s8);
	screems.push_back(s9);
}




