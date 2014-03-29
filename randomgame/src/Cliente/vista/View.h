#pragma once
#ifndef __VIEW_H_
#define __VIEW_H_
#define DEFAULT_COLOR 0x00000000
#include <SDL2_gfxPrimitives.h>
#include "SDLScreen.h"

class View
{
	int x;
	int y;
	Uint32 color;
	
public:
	View(int x, int y, Uint32 color = DEFAULT_COLOR);
	~View(void);

	/** Set the view to initial state */
	virtual void clean();
	/** Update the view */
	virtual void update();
	/** Draw on screen */
	virtual void draw(SDLScreen & screen) = 0;

	int getX() { return x;}
	int getY() { return y;}
	Uint32 getColor() { return color;}

	void setX(int x) {this->x = x;}
	void setY(int y) {this->y = y;}
	void setColor(Uint32 color) { this->color = color;}


};


#endif /* defined(__VIEW_H_) */