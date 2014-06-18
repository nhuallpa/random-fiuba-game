#pragma once

#ifndef __TIMER_VIEW_H__
#define __TIMER_VIEW_H__
#include "TextureManager.h"
#include "View.h"
#include "TextView.h"
#include "../../utils/Constantes/Colors.h"
#include "../../utils/Timer.h"
class TimerView: public View
{
private:

	TextView label;
	Timer timmer;
	float timerP;
	bool finished;
	int index;

public:
	TimerView(int x, int y);

	void clean();
	
	void update();

	void draw(SDLScreen & screen);

	void start();

	void reset();

	bool isFinished();

	void setTimer(float t);

	~TimerView(void);

};

#endif /** __TIMER_VIEW_H__ **/