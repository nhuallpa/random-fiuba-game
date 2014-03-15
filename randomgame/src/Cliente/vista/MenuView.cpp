/*
 * MenuView.cpp
 *
 *  Created on: 09/09/2013
 *      Author: ALiguori
 */

#include "MenuView.h"
#include "Sprites.h"

void MenuView::render(){

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
						Screen::getInstance()->getHeight() );

	
	//Fill the rectangles

	SDL_Rect fillRectHorizontal = { 0,
									Screen::getInstance()->getHeight() - USER_BAR_HEIGHT,
									Screen::getInstance()->getWidth() - MENU_WIDTH,
									Screen::getInstance()->getHeight()
									};

	SDL_SetRenderDrawColor( Screen::getInstance()->getRenderer(), 0xFF, 0xFF, 0x00, 0xFF );
	SDL_RenderFillRect( Screen::getInstance()->getRenderer(), &fillRectHorizontal );

	SDL_Rect fillRectVertical = { 	Screen::getInstance()->getWidth() - MENU_WIDTH,
									0,
									Screen::getInstance()->getWidth(),
									Screen::getInstance()->getHeight()
								};

	SDL_SetRenderDrawColor( Screen::getInstance()->getRenderer(), 0xFF, 0xFF, 0x00, 0xFF );
	SDL_RenderFillRect( Screen::getInstance()->getRenderer(), &fillRectVertical );

	//Draw arrows (up and down)
	Sprites::getInstance()->getSprite(Sprites::getInstance()->getSpriteMap()->size()-3)->renderFixSize(
				Screen::getInstance()->getWidth() - MENU_WIDTH + ALIGN_SPRITE,
				ARROW_Y_POS,
				SPRITES_WIDTH,
				SPRITES_HEIGHT,
				180
				);


	Sprites::getInstance()->getSprite(Sprites::getInstance()->getSpriteMap()->size()-3)->renderFixSize(
			Screen::getInstance()->getWidth() - MENU_WIDTH + ALIGN_SPRITE,
			Screen::getInstance()->getHeight() - SPRITES_HEIGHT - ARROW_Y_POS,
			SPRITES_WIDTH,
			SPRITES_HEIGHT,
			0
			);


	// Draw load background and save buttons
	Sprites::getInstance()->getSprite(Sprites::getInstance()->getSpriteMap()->size()-1)->renderFixSize(
			Screen::getInstance()->getWidth() - MENU_WIDTH - 160 + 15,
			Screen::getInstance()->getHeight() - SPRITES_HEIGHT - ARROW_Y_POS,
			SPRITES_WIDTH,
			SPRITES_HEIGHT,
			0
			);

	Sprites::getInstance()->getSprite(Sprites::getInstance()->getSpriteMap()->size()-2)->renderFixSize(
			Screen::getInstance()->getWidth() - MENU_WIDTH - 160 + 30 + SPRITES_WIDTH,
			Screen::getInstance()->getHeight() - SPRITES_HEIGHT - ARROW_Y_POS,
			SPRITES_WIDTH,
			SPRITES_HEIGHT,
			0
			);



	//Draw Sprites (just first 5) - TODO Cambiar a algo dinamico (que dibuje lo que entre)
	for ( int i=0; i < 4 ; i++ )
		Sprites::getInstance()->getSprite(i)->renderFixSize( Screen::getInstance()->getWidth() - MENU_WIDTH + ALIGN_SPRITE,
															 ARROW_Y_POS + ((ARROW_Y_POS + SPRITES_HEIGHT)*(i+1)),
															 SPRITES_WIDTH,
															 SPRITES_HEIGHT,
															 0
															 );


}
