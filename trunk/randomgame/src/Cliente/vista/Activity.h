#pragma once


#ifndef __ACTIVITY_H_
#define __ACTIVITY_H_
#include "SDLScreen.h"
#include "View.h"
class Activity
{
private:
	SDLScreen m_screen;
	View* aView;

protected:
	/** Clear windows to draw view*/
	void clear();

	/** Set the view to draw on window*/
	void setContentView(View * newView);

public:

	Activity(const SDLScreen & screen);

	~Activity(void);

	/** Update the view*/
	void update();

	/** Render the view on screen*/
	void render();

};

#endif /* defined(__ACTIVITY_H_) */
