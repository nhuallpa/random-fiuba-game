#pragma once
#ifndef __SDLSCREEN_H_
#define __SDLSCREEN_H_

#include "TScreen.h"
#include <string>
#include <sstream>
#include <SDL.h>
#include <SDL_image.h>
class SDLScreen : public TScreen
{
private:
	SDL_Window* m_pWindow;

	SDL_Renderer* renderer;
	
	std::string title;

public:
	
	SDLScreen(void);

	void init(const char* title, int xpos, int ypos, int width,
			int height, int flags);
	
	void clear();
	
	void render();
	
	void terminate();

	void setState(std::string string_state);

	SDL_Renderer* getRenderer();

	~SDLScreen(void);
};

#endif /* defined(__SDLSCREEN_H_) */