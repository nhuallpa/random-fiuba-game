#pragma once
#ifndef __GAME_ACTIVITY_H_
#define __GAME_ACTIVITY_H_
#include <iostream>
#include "Activity.h"
#include "GameViewBuilder.h"
#include "../controlador/GameController.h"
#include "../../Servidor/modelo/GameLevel.h"

class GameActivity : public Activity
{
private:
	
	GameLevel* cLevel;

	GameController* cController;

public:
	GameActivity(const SDLScreen & screen, GameViewBuilder & builder, GameLevel * cLevel, GameController* cController);

	void buildView( GameViewBuilder & builder);

	void update();

	void onCreate();

	void setListeners();

	~GameActivity(void);
};

#endif /* defined(__GAME_ACTIVITY_H_) */

