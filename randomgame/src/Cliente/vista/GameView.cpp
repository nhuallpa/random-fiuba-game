/*
 * GameView.cpp
 *
 *  Created on: 09/09/2013
 *      Author: ALiguori
 */

#include "GameView.h"
#include "Sprites.h"
#include "../../utils/Log.h"

bool GameView::init(){

	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		Log::e( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Enable VSync
		if( !SDL_SetHint( SDL_HINT_RENDER_VSYNC, "1" ) )
		{
			Log::e( "Warning: VSync not enabled!" );
		}

		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			Log::e( "Warning: Linear texture filtering not enabled!" );
		}
	}
	//ToDo: Tomar datos de tamano del parser
	//ParserYaml* aParser = ParserYaml::getInstance();
	this->vScreen = Screen::getInstance();
	this->vScreen->init("Random Game",640,480);

	//this->vScreen->init(aParser->getNivelNombre(),
	//					atoi(aParser->getNivelAncho().c_str()),
	//					atoi(aParser->getNivelAlto().c_str()));

	// Load text
	//this->fontTextures[0].setRenderer(Screen::getInstance()->getRenderer());
	//this->fontTextures[1].setRenderer(Screen::getInstance()->getRenderer());
	//this->loadFonts();


	int i=0;

	//for(;i<aParser->getCantDataElem();i++){
	//	Sprites::getInstance()->addSprite(aParser->getElementPosition(aParser->getDataElemNombre(i)),
	//									  aParser->getImagePath(aParser->getDataElemNombre(i)) );
	//}

	
	Sprites::getInstance()->addSprite(i,"image/bricks.jpg");
	i++;

	//ToDo: Agrego el background en pos siguiente
	//this->loadBackground(i,aParser->getNivelFondo());
	//i++;
	//Agrego boton de flechas, exit, save y cambio de fondo

	Sprites::getInstance()->addSprite(i,"image/arrow.png");
	i++;
	Sprites::getInstance()->addSprite(i,"image/exit.png");
	i++;
	Sprites::getInstance()->addSprite(i,"image/save.png");
	i++;
	Sprites::getInstance()->addSprite(i,"image/change.png");

	//this->menu.init();

	return success;

}

void GameView::loadBackground(int pos, std::string str){
	this->background = str;
	Sprites::getInstance()->addSprite(pos,str);
}


void GameView::close()
{
	Screen::getInstance()->close();
	IMG_Quit();
	SDL_Quit();
}


bool GameView::loadFonts(){

	bool success = true;
	if( !fontTextures[0].loadFromRenderedText( "Background:", this->gameFont.getTextColor(), this->gameFont.getFont() ) )
		{
			Log::e( "Failed to render prompt text!\n" );
			success = false;
		}

	return success;
}

bool GameView::loadSprite(int type, std::string spritePath){

	bool success = true;
	//this->spritesTextures[type].setRenderer(Screen::getInstance()->getRenderer());
	//if( !this->spritesTextures[type].loadFromFile(spritePath) )
	//{
	//	Log::e("Failed to load sprite texture!\n");
	//	success = false;
	//}
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
	//this->drawMenu();
	//this->drawText();

	SDL_RenderPresent( Screen::getInstance()->getRenderer() );

}

void GameView::moveToEnd(const std::list<ElementView>::iterator el){
	this->elems.splice( this->elems.end(), this->elems, el );
}

void GameView::removeElement(ElementView el){
	this->elems.remove(el);
}

void GameView::addElement(ElementView el){
	this->elems.push_back(el);
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
	//fontTextures[0].renderFonts( 20, Screen::getInstance()->getHeight() - 10 - fontTextures[0].getHeight()*2 );
	fontTextures[1].renderFonts( 20, Screen::getInstance()->getHeight() - 10 - 40);
}


void GameView::addElement(int type, float posX, float posY, int degree){
	this->elems.push_back(ElementView(type,posX,posY,degree,Sprites::getInstance()->getSprite(type)));

}

std::list<ElementView>* GameView::getElems(){
	return &this->elems;
}

Screen* GameView::getScreen(){
	return Screen::getInstance();
}


void GameView::drawBackground(){
	Sprites::getInstance()->getSprite(Sprites::getInstance()->getSpriteMap()->size()-5)->renderFixSize(0,
			0,
			Screen::getInstance()->getWidth(),
			Screen::getInstance()->getHeight(),
			0);
}


void GameView::moveMenuUp(){
	this->menu.moveUp();
}

void GameView::moveMenuDown(){
	this->menu.moveDown();
}

int GameView::getMenuOffset(){
	return this->menu.getOffset();
}

std::string GameView::getBackground(){
	return this->background;

}

void GameView::setBackground(std::string b){
	this->background = b;

}