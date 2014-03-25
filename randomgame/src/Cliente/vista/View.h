#pragma once
#ifndef __VIEW_H_
#define __VIEW_H_

#include "SDLScreen.h"

class View
{
	int x;
	int y;
	int width;
	int height;

public:
	View(int x, int y, int width, int height);
	~View(void);

	/** Set the view to initial state */
	virtual void clean() = 0;
	/** Update the view */
	virtual void update() = 0;
	/** Draw on screen */
	virtual void draw(SDLScreen & screen) = 0;

	int View::getX() { return x;}
	int View::getY() { return y;}
	int View::getWidth() { return width;}
	int View::getHeight() { return height;}

	void View::setX(int x) {this->x = x;}
	void View::setY(int y) {this->y = y;}
	void View::setWidth(int width) {this->width = width;}
	void View::setHeight(int height) {this->height = height;}

};


#endif /* defined(__VIEW_H_) */