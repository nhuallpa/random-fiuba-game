#pragma once
#ifndef __VIEW_H_
#define __VIEW_H_
#define DEFAULT_COLOR "0xFFFFFFFF"
#include <SDL2_gfxPrimitives.h>
#include <string>
#include <sstream>
#include <iostream>
#include "SDLScreen.h"
#include "GameException.h"
#include "../../utils/Util.h"


class View
{
	int x;
	int y;
	std::string color;
	std::string borderColor;
	
	Uint32 convertToInt(std::string aColor);
	
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
	std::string getBorderColor() { return borderColor;}

	Uint32 getColorCod();
	Uint32 getBorderColorCod();
	
	
	void setX(int x) {this->x = x;}
	void setY(int y) {this->y = y;}
	void setColor(std::string color) { this->color = color;}
	void setBorderColor(std::string color) { this->borderColor = color;}

	void swapEndian(Uint32 *colorCode);

	

};


#endif /* defined(__VIEW_H_) */