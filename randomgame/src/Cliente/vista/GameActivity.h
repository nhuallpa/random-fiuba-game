#pragma once
#ifndef __GAME_ACTIVITY_H_
#define __GAME_ACTIVITY_H_
#include <iostream>
#include "Activity.h"
#include "ViewBuilder.h"

class GameActivity : public Activity
{
private:
	
	ViewGroup * viewContainer;

public:
	GameActivity(const SDLScreen & screen, ViewBuilder & builder);

	View* buildView( ViewBuilder & builder);

	void onCreate();

	~GameActivity(void);
};

#endif /* defined(__GAME_ACTIVITY_H_) */

