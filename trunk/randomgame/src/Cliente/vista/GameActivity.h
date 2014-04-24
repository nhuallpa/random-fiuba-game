#pragma once
#ifndef __GAME_ACTIVITY_H_
#define __GAME_ACTIVITY_H_
#include <iostream>
#include "Activity.h"
#include "ViewBuilder.h"
#include "../../Servidor/modelo/GameLevel.h"

class GameActivity : public Activity
{
private:
	
	GameLevel* cLevel;

	FigureViewGroup* figureContainer;



public:
	GameActivity(const SDLScreen & screen, ViewBuilder & builder, GameLevel * cLevel);

	ViewGroup* buildView( ViewBuilder & builder);

	void update();

	void onCreate();

	~GameActivity(void);
};

#endif /* defined(__GAME_ACTIVITY_H_) */

