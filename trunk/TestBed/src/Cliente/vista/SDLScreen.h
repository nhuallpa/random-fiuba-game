#pragma once
#ifndef __SDLSCREEN_H_
#define __SDLSCREEN_H_

#include "TScreen.h"
#include <string>
#include <sstream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "../../utils/Log.h"
#include "Camera.h"
#include "../controlador/Contracts/OnZoomListener.h"
class SDLScreen : public TScreen, public OnZoomListener
{
private:
	SDL_Window* m_pWindow;

	SDL_Renderer* renderer;
	
	std::string title;

	float scale;

	Camera * refCam;

public:
	
	SDLScreen(void);

	void init(const char* title, int xpos, int ypos, int width,
			int height, int flags);
	
	void setCamera(Camera * camera) { refCam = camera;}
	void clear();
	
	void render();
	
	void terminate();

	void setState(std::string string_state);

	void OnZoom(ZoomEvent e);

	SDL_Renderer* getRenderer();


	~SDLScreen(void);
};

#endif /* defined(__SDLSCREEN_H_) */