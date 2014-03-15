/*
 * GameFonts.h
 *
 *  Created on: 20/09/2013
 *      Author: aliguori
 */
#pragma once

#ifndef GAMEFONTS_H_
#define GAMEFONTS_H_

#include <SDL_ttf.h>
#include <stdio.h>
/*
 *
 */
class GameFonts {
public:
	GameFonts();
	virtual ~GameFonts();
	TTF_Font* getFont();
	SDL_Color getTextColor();

private:
	TTF_Font *gFont;
	SDL_Color textColor;
};

#endif /* GAMEFONTS_H_ */
