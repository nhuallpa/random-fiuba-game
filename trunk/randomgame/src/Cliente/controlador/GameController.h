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
#include "../../utils/PersistYaml.h"
//#include "../../utils/utils.h"


class GameController {
public:
	GameController();
	GameController(GameLevel* gL, GameView* gV);
	virtual ~GameController();
	bool init();
	void detectEvents();
	bool handleEvents();
	ElementView* checkInsideElements();
	ElementView* checkInsideMenu();
	bool getChanges();
	void updateElements();

private:
	GameView *gView;
	ElementView* currentElement;
	ElementView* currentMenuElement;
	GameLevel* cLevel;
	Detector cDetector;
	bool changes;
	std::pair<float,float> lastElemPos;

	void persist();
	bool checkSaveRequested();
	bool checkChangeBackground();
	bool checkMoveDownRequested();
	bool checkMoveUpRequested();
	bool checkExitRequested();


};

#endif /* GAMECONTROLLER_H_ */
