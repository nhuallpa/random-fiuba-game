/*
 * Detector.h
 *
 *  Created on: 09/09/2013
 *      Author: ALiguori
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
#include <list>
#include "../vista/Screen.h"
#include "GameButton.h"



/*
 *
 */


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

#endif /* DETECTOR_H_ */
