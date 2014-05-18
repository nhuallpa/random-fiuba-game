#pragma once


#ifndef __ACTIVITY_H_
#define __ACTIVITY_H_
#include "SDLScreen.h"
#include "ViewGroup.h"

class Activity
{
private:
	SDLScreen m_screen;

protected:
	/** Clear windows to draw view*/
	void clear();

	/** Set the view to draw on window*/
	void setContentView(ViewGroup * newView);

	ViewGroup* aView;

	

public:

	Activity(SDLScreen & screen);

	virtual ~Activity(void);

	/** Update the view*/
	virtual void update();

	/** Render the view on screen*/
	void render();

	virtual void setMessageView(std::string msg);

};

#endif /* defined(__ACTIVITY_H_) */
