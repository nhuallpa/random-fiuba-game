#pragma once
#ifndef __VIEW_H_
#define __VIEW_H_
#define DEFAULT_COLOR "0xFFFFFFFF"
#include <SDL2_gfxPrimitives.h>
#include <string>
#include <sstream>
#include <iostream>
#include "SDLScreen.h"


typedef struct t_color {
	Uint8 r;
	Uint8 g;
	Uint8 b;
	Uint8 a;
} tColor;

class View
{
	int x;
	int y;
	std::string color;
	
public:
	View(int x, int y, std::string color = DEFAULT_COLOR);
	virtual ~View(void);

	/** Set the view to initial state */
	virtual void clean();
	/** Update the view */
	virtual void update();
	/** Draw on screen */
	virtual void draw(SDLScreen & screen) = 0;

	int getX() { return x;}
	int getY() { return y;}
	std::string getColor() { return color;}

	Uint32 getColorCod();
	tColor getColorRGBA();

	void setX(int x) {this->x = x;}
	void setY(int y) {this->y = y;}
	void setColor(std::string color) { this->color = color;}

	void swapEndian(Uint32 *colorCode);

};


#endif /* defined(__VIEW_H_) */