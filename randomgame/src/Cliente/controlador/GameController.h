/*
 * GameController.h
 *
 *  Created on: 09/09/2013
 *      Author: ALiguori
 */
#pragma once

#ifndef GAMECONTROLLER_H_
#define GAMECONTROLLER_H_

#include <iostream>
#include "Detector.h"
#include "../../Servidor/modelo/GameLevel.h"
#include "../../Servidor/modelo/GameElement.h"
#include "../vista/GameView.h"


class GameController {
public:
	GameController();
	GameController(GameLevel* gL, GameView* gV);
	virtual ~GameController();
	bool getState(State action);
	bool init();
	void clearStates();
	void detectEvents();
	void handleEvents();
	void setState(State action, bool value);
	ElementView* checkInsideElements();
	ElementView* checkInsideMenu();
	bool getChanges();

private:
	GameView *gView;
	ElementView* currentElement;
	ElementView* currentMenuElement;
	GameLevel* cLevel;
	Detector cDetector;
	bool cState[TOTAL_STATES];
	bool changes;


	bool checkSaveRequested();
	bool checkChangeBackground();

};

#endif /* GAMECONTROLLER_H_ */
