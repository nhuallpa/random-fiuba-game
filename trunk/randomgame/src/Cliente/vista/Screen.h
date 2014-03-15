/*
 * Screen.h
 *
 *  Created on: 09/09/2013
 *      Author: ALiguori
 */
#pragma once

#ifndef SCREEN_H_
#define SCREEN_H_

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include "Textures.h"
// #include "ElementView.h"
// #include "MenuView.h"

//Screen dimension constants


/*
 *
 */
class Screen {
public:

	virtual ~Screen();
	static Screen *getInstance();
	int getHeight();
	int getWidth();
	bool init();
	void close();
	void clearScreen();
	SDL_Renderer* getRenderer();
	bool hasMouseFocus();
	bool hasKeyboardFocus();
	void setHeight(int h);
	void setWidth(int w);
	void setMouseFocus(bool f);
	void setKeyboardFocus(bool f);
	std::pair<float,float> getLogic2PixelsFactor();


private:
	SDL_Renderer* vRenderer;
	SDL_Window* vWindow;
	Textures myTextures;
	//ElementView* myElements;
	//MenuView myMenu;
	static Screen *instance;

	//Singleton
	Screen();

	int height;
	int width;

	bool sMouseFocus;
	bool sKeyboardFocus;
	bool sFullScreen;

};

#endif /* SCREEN_H_ */
