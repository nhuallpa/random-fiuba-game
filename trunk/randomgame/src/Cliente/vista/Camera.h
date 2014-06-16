#pragma once
#ifndef __CAMERA_H__
#define __CAMERA_H__
#include <SDL.h>
#include "../controlador/Contracts/OnScrollListener.h"
#include "../../utils/Log.h"

typedef enum {
	FOCUS_BOTOOM_CENTER,
	FOCUS_CENTER
} tFocus;

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
	void setW(int w) { this->box.w = w;}
	void setH(int h) { this->box.h = h;}
	int getWidthScenario() {return this->widthScenario;}
	int getHeightScenario() {return this->heightScenario;}
	void setWidthScenario(int w) { this->widthScenario = w;}
	void setHeightScenario(int h) {this->heightScenario = h;}

	void OnScroll(ScrollEvent e);

	void setFocus(tFocus tipo, int dest_w, int dest_h);

	~Camera(void);
};

#endif