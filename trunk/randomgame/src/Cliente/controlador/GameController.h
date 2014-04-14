
#pragma once

#ifndef GAMECONTROLLER_H_
#define GAMECONTROLLER_H_

#include <iostream>
#include "Detector.h"
#include "../../Servidor/modelo/GameLevel.h"
#include "../../Servidor/modelo/GameElement.h"
//#include "../vista/GameView.h"
#include "../../utils/PersistYaml.h"
//#include "../../utils/utils.h"


class GameController {
public:
	GameController();
	GameController(GameLevel* gL);
	virtual ~GameController();
	void detectEvents();
	void handleEvents();
	void clearStates();
	bool isBeginLife();
	bool isRegenerateWorld();
	bool isPause();
	bool isQuit();

	bool init();
	//ElementView* checkInsideElements();
	//ElementView* checkInsideMenu();
	bool getChanges();
	void updateElements();

private:
	Detector cDetector;



	/*GameView *gView;
	ElementView* currentElement;
	ElementView* currentMenuElement;*/
	GameLevel* cLevel;
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
