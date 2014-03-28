/*
 * Detector.h
 *
 *  Created on: 01/03/2014
 *      Author: ALiguori/eschmoll
 */

#pragma once

#ifndef DETECTOR_H_
#define DETECTOR_H_

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <map>
#include <vector>
#include <algorithm>
#include <iostream>
#include "../vista/Screen.h"
#include "GameButton.h"

using namespace std;

/*
 *
 */

enum State{
	BEGIN_LIFE = 0,
	REGENERATE_WORLD = 1,
	PAUSE = 2,
	EXIT_REQUEST=3,
	TOTAL_STATES=4
};


class Detector {
public:
	Detector();
	virtual ~Detector();
	void init();
	void detect();
	void clearStates();
	bool isBeginLife();
	bool isRegenerateWorld();
	bool isPuase();
	bool isQuit();
	bool getState(State action);
	void setState(State action, bool value);

private:
	enum TypeElement{SBUTTON, PBUTTON};
	map<TypeElement, GameButton*> Elements;
	const Uint8* m_keys;
	bool quit;
	bool cState[TOTAL_STATES];
	void createButtons();
	void destroyButtons();
	void handleEventKeys();
	void handleEvents(SDL_Event* e);
	GameButton* getElement(TypeElement te);
};

#endif /* DETECTOR_H_ */









/******************************************************************
#pragma once

#ifndef DETECTOR_H_
#define DETECTOR_H_

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <map>
#include <vector>
#include <algorithm>
#include <iostream>
#include <list>
#include "../vista/Screen.h"
#include "GameButton.h"




enum State{
	MOUSE_LEFT_PRESSED=0,
	MOUSE_RIGHT_PRESSED=1,
	MOUSE_MOVING=2,
	MOUSE_RELEASED=3,
	KB_SHIFT_PRESSED=4,
	KB_UP_ARROW=5,
	KB_DOWN_ARROW=6,
	EXIT_REQUEST=7,
	INPUT_TXT_CHGD=8,
	WNDW_SIZE_CHGD=9,
	KB_ENTER_PRESSED=10,
	TOTAL_STATES=11
};



class Detector {
public:
	Detector();
	virtual ~Detector();
	void detect();
	void handleEvents(SDL_Event* e);
	std::pair<int,int> getMousePosition();
	std::pair<int,int> getMouseRelativePosition();
	bool getState(State action);
	void clearStates();
	void setState(State action, bool value);
	void clearMousePosition();
	bool changedRelPosition();
	std::string getBackgroundText();
	void setLastMousePosition(int x, int y);
	std::pair<int,int> getLastMousePosition();



private:
	bool changedPosition;
	std::pair<int,int> mousePosition;
	std::pair<int,int> lastMousePosition;
	std::pair<int,int> mouseRelativePosition;
	bool cState[TOTAL_STATES];
	//SDL_Event event;
	std::string backgroundText;
	// Mod-18 Begin
	void createButtons();
	void destroyButtons();
	void handleEventKeys();
	SDL_Window* view;
	std::list<GameButton*> l_buttons;
	const Uint8* m_keys;
	// Mod-18 End	
};



**********************************************************************/
