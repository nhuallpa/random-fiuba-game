/*
 * GameView.h
 *
 *  Created on: 09/09/2013
 *      Author: ALiguori
 */
#pragma once

#ifndef GAMEVIEW_H_
#define GAMEVIEW_H_

#include <SDL.h>
#include <SDL_image.h>
#include "GameFonts.h"
#include "Textures.h"
#include "../../Servidor/modelo/GameLevel.h"
#include <vector>
#include <map>
#include <algorithm>
#include <list>
#include "../../Servidor/modelo/GameElement.h"
#include "Screen.h"
#include "MenuView.h"
#include "ElementView.h"






enum sprites
{
	CIRCLE_SPRITE = 0,
	SQUARE_SPRITE = 1,
	PENTAGON_SPRITE = 2,
	TRIANGLE_SPRITE = 3,
	TOTAL_SPRITES = 4
};


class GameView{

	private:

		void drawMenu();
		void drawText();
		void drawBackground();
		void renderLevel();
		bool loadFonts();

		Textures spritesTextures[TOTAL_SPRITES];
		Textures fontTextures[2];
		Screen* vScreen;
		std::list<ElementView> elems;
		MenuView menu;

	public:
		Screen* getScreen();
		std::list<ElementView>* getElems();
		GameFonts gameFont;

		void close();
		bool init();
		bool loadSprite(int type, std::string spritePath);
		void render();
		void clearScreen();
		void addElement(int type, int posX, int posY, int degree);
		void drawInputText(std::string inputText);
};

#endif /* GAMEVIEW_H_ */
