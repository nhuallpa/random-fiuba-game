#pragma once
#ifndef __CAMERA_H__
#define __CAMERA_H__
#include <SDL.h>
#include "../controlador/Contracts/OnScrollListener.h"
class Camera : public OnScrollListener
{
	SDL_Rect box;
	int widthScenario;
	int heightScenario;
	
public:
	Camera();

	void setDimension(int w, int h);
	void setPosition(int x, int y);
	int getX() { return this->box.x;}
	int getY() { return this->box.y;}
	int getW() { return this->box.w;}
	int getH() { return this->box.h;}
	int getWidthScenario() {return this->widthScenario;}
	int getHeightScenario() {return this->heightScenario;}
	void setWidthScenario(int w) { this->widthScenario = w;}
	void setHeightScenario(int h) {this->heightScenario = h;}

	void OnScroll(ScrollEvent e);

	~Camera(void);
};

#endif