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
#include "../../utils/PersistYaml.h"


class GameView{

	private:

		void drawMenu();
		void drawText();
		void drawBackground();
		void renderLevel();
		bool loadFonts();

		//Textures spritesTextures[TOTAL_SPRITES];
		Textures fontTextures[2];
		Screen* vScreen;
		std::list<ElementView> elems;
		MenuView menu;
		std::string background;

	public:
		Screen* getScreen();
		std::list<ElementView>* getElems();
		GameFonts gameFont;
		void moveToEnd(std::list<ElementView>::iterator el);
		void removeElement(ElementView el);

		void setBackground(std::string b);
		std::string getBackground();
		void loadBackground(int pos,std::string str);
		void close();
		bool init();
		bool loadSprite(int type, std::string spritePath);
		void render();
		void clearScreen();
		void addElement(int type, float posX, float posY, int degree);
		void addElement(ElementView el);
		void drawInputText(std::string inputText);
		void moveMenuUp();
		void moveMenuDown();
		int getMenuOffset();
};

#endif /* GAMEVIEW_H_ */
