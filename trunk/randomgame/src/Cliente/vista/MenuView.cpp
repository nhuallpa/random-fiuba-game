/*
 * MenuView.cpp
 *
 *  Created on: 09/09/2013
 *      Author: ALiguori
 */

#include "MenuView.h"
#include "Sprites.h"
#include <math.h>

void MenuView::init(){
	for ( int i=0; i < Sprites::getInstance()->getSpriteMap()->size()-6 ; i++ ){
		//std::cout << "added" << i << std::endl;
		this->trMap[i] = Sprites::getInstance()->getSprite(i);
	}
	this->offset = 0;
}

void MenuView::render(){

	//Fill the rectangles
	SDL_Rect fillRectHorizontal = { 20,
									Screen::getInstance()->getHeight() - 10 - 40,
									(Screen::getInstance()->getWidth() - MENU_WIDTH - (SPRITES_WIDTH*3) - (15*5)),
									30
									};

	Sprites::getInstance()->getSprite(Sprites::getInstance()->getSpriteMap()->size()-6)->renderFixSize(
				0,
				Screen::getInstance()->getHeight() - USER_BAR_HEIGHT,
				Screen::getInstance()->getWidth(),
				USER_BAR_HEIGHT,
				0
				);

	SDL_SetRenderDrawColor( Screen::getInstance()->getRenderer(), 0xFF, 0xFF, 0x00, 0xFF );

	SDL_RenderFillRect( Screen::getInstance()->getRenderer(), &fillRectHorizontal );

	//SDL_Rect fillRectVertical = { 	Screen::getInstance()->getWidth() - MENU_WIDTH,
	//								0,
	//								Screen::getInstance()->getWidth(),
	//								Screen::getInstance()->getHeight()
	//							};

	//SDL_SetRenderDrawColor( Screen::getInstance()->getRenderer(), 0xFF, 0xFF, 0x00, 0xFF );
	//SDL_RenderFillRect( Screen::getInstance()->getRenderer(), &fillRectVertical );

	Sprites::getInstance()->getSprite(Sprites::getInstance()->getSpriteMap()->size()-6)->renderFixSize(
				Screen::getInstance()->getWidth() - MENU_WIDTH,
				0,
				MENU_WIDTH,
				Screen::getInstance()->getHeight(),
				0
				);


	//Draw horizontal line for limit user bar action
	SDL_SetRenderDrawColor( Screen::getInstance()->getRenderer(), 0x00, 0x00, 0xFF, 0xFF );
//	 *  \param renderer The renderer which should draw a line.
//	 *  \param x1 The x coordinate of the start point.
//	 *  \param y1 The y coordinate of the start point.
//	 *  \param x2 The x coordinate of the end point.
//	 *  \param y2 The y coordinate of the end point.
	SDL_RenderDrawLine( Screen::getInstance()->getRenderer(),
						0,
						Screen::getInstance()->getHeight() - USER_BAR_HEIGHT,
						Screen::getInstance()->getWidth() - MENU_WIDTH,
						Screen::getInstance()->getHeight() - USER_BAR_HEIGHT );

	//Draw vertical line for limit the rigth menu of chosing images
	SDL_RenderDrawLine( Screen::getInstance()->getRenderer(),
						Screen::getInstance()->getWidth() - MENU_WIDTH,
						0,
						Screen::getInstance()->getWidth() - MENU_WIDTH,
						Screen::getInstance()->getHeight() - USER_BAR_HEIGHT );
	
	//Orden de elementos: boton de flechas, exit, save y cambio de fondo

	//Draw arrows (up and down)
	Sprites::getInstance()->getSprite(Sprites::getInstance()->getSpriteMap()->size()-4)->renderFixSize(
				Screen::getInstance()->getWidth() - MENU_WIDTH + ALIGN_SPRITE,
				ARROW_Y_POS,
				SPRITES_WIDTH,
				SPRITES_HEIGHT,
				180
				);


	Sprites::getInstance()->getSprite(Sprites::getInstance()->getSpriteMap()->size()-4)->renderFixSize(
			Screen::getInstance()->getWidth() - MENU_WIDTH + ALIGN_SPRITE,
			Screen::getInstance()->getHeight() - SPRITES_HEIGHT - ARROW_Y_POS,
			SPRITES_WIDTH,
			SPRITES_HEIGHT,
			0
			);


	// Draw exit, save and load background buttons
	Sprites::getInstance()->getSprite(Sprites::getInstance()->getSpriteMap()->size()-3)->renderFixSize(
			Screen::getInstance()->getWidth() - MENU_WIDTH - (SPRITES_WIDTH*3) - (15*3),
			Screen::getInstance()->getHeight() - SPRITES_HEIGHT - ARROW_Y_POS,
			SPRITES_WIDTH,
			SPRITES_HEIGHT,
			0
			);

	Sprites::getInstance()->getSprite(Sprites::getInstance()->getSpriteMap()->size()-2)->renderFixSize(
			Screen::getInstance()->getWidth() - MENU_WIDTH - (SPRITES_WIDTH*2) - (15*2),
			Screen::getInstance()->getHeight() - SPRITES_HEIGHT - ARROW_Y_POS,
			SPRITES_WIDTH,
			SPRITES_HEIGHT,
			0
			);

	Sprites::getInstance()->getSprite(Sprites::getInstance()->getSpriteMap()->size()-1)->renderFixSize(
			Screen::getInstance()->getWidth() - MENU_WIDTH - (SPRITES_WIDTH*1) - (15*1),
			Screen::getInstance()->getHeight() - SPRITES_HEIGHT - ARROW_Y_POS,
			SPRITES_WIDTH,
			SPRITES_HEIGHT,
			0
			);


	//Draw Sprites (just first 5) - TODO Cambiar a algo dinamico (que dibuje lo que entre)
//	for ( int i=0; i < 4 ; i++ ){
//		Sprites::getInstance()->getSprite(i)->renderFixSize( Screen::getInstance()->getWidth() - MENU_WIDTH + ALIGN_SPRITE,
//															 ARROW_Y_POS + ((ARROW_Y_POS + SPRITES_HEIGHT)*(i+1)),
//															 SPRITES_WIDTH,
//															 SPRITES_HEIGHT,
//															 0
//															 );
//
//	}

	int qtyMenuElems = ( Screen::getInstance()->getHeight() - (SPRITES_HEIGHT*2) - (ARROW_Y_POS*2) ) / (ARROW_Y_POS + SPRITES_HEIGHT);
	//std::cout << "menu elems: " << qtyMenuElems << std::endl;
	if ( qtyMenuElems > (this->trMap.size()-1) ){
		qtyMenuElems = this->trMap.size();
	}

	for ( int i=0; i < qtyMenuElems ; i++ ){
		this->trMap[i]->renderFixSize( 	Screen::getInstance()->getWidth() - MENU_WIDTH + ALIGN_SPRITE,
										ARROW_Y_POS + ((ARROW_Y_POS + SPRITES_HEIGHT)*(i+1)),
										SPRITES_WIDTH,
										SPRITES_HEIGHT,
										0
										);
	}


}


void MenuView::moveUp(){

	int i=0;
	Textures* aux = this->trMap[0];
	for ( ; i < this->trMap.size()-1 ; i++ ){
		this->trMap[i] = this->trMap[i+1];
	}
	this->trMap[i] = aux;
	this->offset++;

}

void MenuView::moveDown(){
	Textures* aux = this->trMap[trMap.size()-1];
	int i=trMap.size()-1;
	for ( ; i > 0 ; i-- ){
		this->trMap[i] = this->trMap[i-1];
	}
	this->trMap[i] = aux;
	this->offset--;

}


int MenuView::getOffset(){
	if ( this->offset >= 0 ){
		return (this->offset%(this->trMap.size()));
	}
	return ( this->trMap.size() - ((abs(this->offset)) % this->trMap.size() ) );
}


