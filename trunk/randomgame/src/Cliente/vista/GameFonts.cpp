/*
 * GameFonts.cpp
 *
 *  Created on: 20/09/2013
 *      Author: aliguori
 */

#include "GameFonts.h"
#include "../../utils/Log.h"

GameFonts::GameFonts() {
	// TODO Auto-generated constructor stub
	
			//Initialize SDL_ttf
	if( TTF_Init() == -1 )
	{
		Log::e("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());

	}

	this->gFont = TTF_OpenFont( "image/arial.ttf", 28 );
	if( this->gFont == NULL )
	{
		Log::e( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
	}

	this->textColor.a = 0;
	this->textColor.b = 0;
	this->textColor.g = 0;
	this->textColor.r = 0xFF;
}

GameFonts::~GameFonts() {
	// TODO Auto-generated destructor stub
}


TTF_Font* GameFonts::getFont(){
	return this->gFont;
}


SDL_Color GameFonts::getTextColor(){
	return this->textColor;
}


