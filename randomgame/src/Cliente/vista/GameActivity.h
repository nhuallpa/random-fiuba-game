#pragma once
#ifndef __GAME_ACTIVITY_H_
#define __GAME_ACTIVITY_H_

#include "Activity.h"
#include "FigureView.h"
#include "SkyView.h"
#include "ViewGroup.h"
#include "WaterView.h"

class GameActivity : public Activity
{
private:
	FigureView * rectView;
	SkyView * skyView;
	WaterView * waterView;
	ViewGroup * viewContainer;

public:
	GameActivity(const SDLScreen & screen);

	void onCreate();

	~GameActivity(void);
};

#endif /* defined(__GAME_ACTIVITY_H_) */

