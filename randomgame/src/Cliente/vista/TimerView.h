#pragma once

#ifndef __TIMER_VIEW_H__
#define __TIMER_VIEW_H__
#include "TextureManager.h"
#include "View.h"
#include "TextView.h"
#include "../../utils/Constantes/Colors.h"
class TimerView: public View
{
private:

	TextView label;

public:
	TimerView(int x, int y);

	void clean();
	
	void update();

	void draw(SDLScreen & screen);

	~TimerView(void);

};

#endif /** __TIMER_VIEW_H__ **/