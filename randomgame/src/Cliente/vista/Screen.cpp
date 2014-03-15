/*
 * Screen.cpp
 *
 *  Created on: 09/09/2013
 *      Author: ALiguori
 */

#include "Screen.h"

Screen *Screen::instance = NULL;

Screen::Screen() {
	this->height = SCREEN_HEIGHT;
	this->width = SCREEN_WIDTH;
	this->sKeyboardFocus = false;
	this->sMouseFocus = false;
	this->vRenderer = NULL;
	this->vWindow = NULL;
	this->sFullScreen = false;

}

Screen::~Screen() {
	this->close();
}

bool Screen::init() {

	//Initialization flag
	bool success = true;

	//Create window
	this->vWindow = SDL_CreateWindow( "TIM v1", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE );
	if( this->vWindow == NULL )
	{
		printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		this->width = SCREEN_WIDTH;
		this->height = SCREEN_HEIGHT;
		this->sMouseFocus = true;
		this->sKeyboardFocus = true;

		//Create renderer for window
		this->vRenderer = SDL_CreateRenderer( this->vWindow, -1, SDL_RENDERER_ACCELERATED );
		if( this->vRenderer == NULL )
		{
			printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Initialize renderer color
			SDL_SetRenderDrawColor( this->vRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

			//Initialize PNG loading
			int imgFlags = IMG_INIT_PNG;
			if( !( IMG_Init( imgFlags ) & imgFlags ) )
			{
				printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
				success = false;
			}
		}
	}

	return success;
}


void Screen::close()
{

	//Destroy window
	SDL_DestroyRenderer( this->vRenderer );
	SDL_DestroyWindow( this->vWindow );
	this->vWindow = NULL;
	this->vRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}



int Screen::getHeight(){
	return this->height;
}


int Screen::getWidth(){
	return this->width;
}


void Screen::clearScreen(){

	SDL_SetRenderDrawColor( this->vRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
	SDL_RenderClear( this->vRenderer );
}


SDL_Renderer* Screen::getRenderer(){
	return this->vRenderer;
}


Screen *Screen::getInstance() {
if(instance == NULL)
    instance = new Screen();

return instance;
}


bool Screen::hasMouseFocus(){
	return this->sMouseFocus;
}


bool Screen::hasKeyboardFocus(){
	return this->sKeyboardFocus;
}


void Screen::setHeight(int h){
	this->height = h;
}

void Screen::setWidth(int w){
	this->width = w;
}

void Screen::setMouseFocus(bool f){
	this->sMouseFocus = f;
}

void Screen::setKeyboardFocus(bool f){
	this->sKeyboardFocus = f;
}

std::pair<float,float> Screen::getLogic2PixelsFactor(){

	return std::make_pair(
			((float)((this->getWidth() - MENU_WIDTH)) / (float)(LOGIC_UNITS)),
			((float)((this->getHeight() - USER_BAR_HEIGHT)) / (float)(LOGIC_UNITS))
			);
}





