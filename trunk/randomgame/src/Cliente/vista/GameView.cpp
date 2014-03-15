/*
 * GameView.cpp
 *
 *  Created on: 09/09/2013
 *      Author: ALiguori
 */

#include "GameView.h"
#include "Sprites.h"

bool GameView::init(){

	//Initialization flag
	bool success = true;



	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Enable VSync
		if( !SDL_SetHint( SDL_HINT_RENDER_VSYNC, "1" ) )
		{
			printf( "Warning: VSync not enabled!" );
		}

		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}
	}


	//TODO Parse YAML para obtener sprites images
	//hardcoded

	this->vScreen = Screen::getInstance();
	this->vScreen->init();

	// Load text
	this->fontTextures[0].setRenderer(Screen::getInstance()->getRenderer());
	this->fontTextures[1].setRenderer(Screen::getInstance()->getRenderer());
	this->loadFonts();

	// TODO Change for bulk load - The last item (SHOULD)would be the arrows!!
	Sprites::getInstance()->addSprite(CIRCLE_SPRITE,"image/circulo.png");
	Sprites::getInstance()->addSprite(SQUARE_SPRITE,"image/cuadrado.png");
	Sprites::getInstance()->addSprite(TRIANGLE_SPRITE,"image/triangulo.png");
	Sprites::getInstance()->addSprite(PENTAGON_SPRITE,"image/pentagono.png");


	//Agrego las imagenes de configuracion ( flechas, boton guardar, boton cambiar background)
	Sprites::getInstance()->addSprite(4,"image/mario-back.jpg");
	Sprites::getInstance()->addSprite(5,"image/arrow.png");
	Sprites::getInstance()->addSprite(6,"image/save.png");
	Sprites::getInstance()->addSprite(7,"image/changeBack.png");

	return success;

}


void GameView::close()
{
	// TODO Destructor
	Screen::getInstance()->close();

	IMG_Quit();
	SDL_Quit();
}


bool GameView::loadFonts(){

	bool success = true;
	if( !fontTextures[0].loadFromRenderedText( "Background:", this->gameFont.getTextColor(), this->gameFont.getFont() ) )
		{
			printf( "Failed to render prompt text!\n" );
			success = false;
		}

	return success;
}

bool GameView::loadSprite(int type, std::string spritePath){

	bool success = true;
	this->spritesTextures[type].setRenderer(Screen::getInstance()->getRenderer());
	if( !this->spritesTextures[type].loadFromFile(spritePath) )
	{
		std::cout << "Failed to load sprite texture!\n" << std::endl;
		success = false;
	}
	return success;
}


void GameView::renderLevel(){
	for (std::list<ElementView>::iterator it=this->elems.begin(); it!=this->elems.end(); ++it)
	    (*it).render();

}

void GameView::drawMenu(){
	this->menu.render();
}


void GameView::clearScreen(){
	this->vScreen->clearScreen();
}

void GameView::render(){
	
	this->drawBackground();
	this->renderLevel();
	this->drawMenu();
	this->drawText();

	SDL_RenderPresent( Screen::getInstance()->getRenderer() );

}


void GameView::drawInputText( std::string inputText ){

	if( inputText != "" )
	{
		fontTextures[1].loadFromRenderedText( inputText.c_str(), this->gameFont.getTextColor(), this->gameFont.getFont() );
	}
	else
	{
		fontTextures[1].loadFromRenderedText( " ", this->gameFont.getTextColor(), this->gameFont.getFont() );
	}
}

void GameView::drawText(){
	fontTextures[0].renderFonts( 20, Screen::getInstance()->getHeight() - 10 - fontTextures[0].getHeight()*2 );
	fontTextures[1].renderFonts( 20, Screen::getInstance()->getHeight() - 10 - fontTextures[1].getHeight());
}


void GameView::addElement(int type, int posX, int posY, int degree){
	this->elems.push_back(ElementView(type,posX,posY,degree,Sprites::getInstance()->getSprite(type)));

}

std::list<ElementView>* GameView::getElems(){
	return &this->elems;
}

Screen* GameView::getScreen(){
	return Screen::getInstance();
}


void GameView::drawBackground(){
	Sprites::getInstance()->getSprite(Sprites::getInstance()->getSpriteMap()->size()-4)->renderFixSize(0,
			0,
			Screen::getInstance()->getWidth(),
			Screen::getInstance()->getHeight(),
			0);
}


