/*
 * GameController.cpp
 *
 *  Created on: 09/09/2013
 *      Author: ALiguori
 */

#include "GameController.h"
#include "../vista/Sprites.h"
#include <math.h>


#define PI 3.14159265


GameController::GameController() {
	// TODO Auto-generated constructor stub

}

GameController::GameController(GameLevel* gL, GameView* gV) {
	this->cLevel = gL;
	this->gView = gV;
	this->currentElement = NULL;
	this->currentMenuElement = NULL;
	this->changes = false;
	//generate a ElemntView per Game Element

}

GameController::~GameController() {
	// TODO Auto-generated destructor stub
}



bool GameController::init(){
	//lee elementos del mundo
	// por cada uno de ellos agrega un ElementView en la vista

	std::multimap<std::pair<float, float>, GameElement> mmap = this->cLevel->getEntities();
	std::multimap<std::pair<float, float>, GameElement>::iterator elems = mmap.begin();



	for ( ; elems != mmap.end(); elems++) {
		//((*elems).first).first; //x - up left corner
		//((*elems).first).second; //y - up left corner
		//((*elems).second)->getType(); // elem type
		//((*elems).second)->getRotation(); // rotation
		//(int type, int posX, int posY, int degree);

		std::cout << "added one at" << (((*elems).first).first * Screen::getInstance()->getLogic2PixelsFactor().first) <<
					", " << (((*elems).first).second * Screen::getInstance()->getLogic2PixelsFactor().second) << std::endl;

		this->gView->addElement(((*elems).second).getType(),
				(((*elems).first).first * Screen::getInstance()->getLogic2PixelsFactor().first),
				(((*elems).first).second * Screen::getInstance()->getLogic2PixelsFactor().second),
				((*elems).second).getRotation());
	}


	return true;
}




bool GameController::getState(State action){
	return this->cState[action];
}


void GameController::clearStates(){
	for (int i=0; i <= TOTAL_STATES; i++){
		this->cState[i] = false;
	}
}

void GameController::setState(State action, bool value){
	this->cState[action] = value;
}

void GameController::detectEvents(){

	//this->cDetector.handleEvents( (this->cDetector.detect()) );
	this->cDetector.detect();
}


ElementView* GameController::checkInsideElements(){

	std::list<ElementView>* mmap = this->gView->getElems();
	std::list<ElementView>::iterator elems = mmap->begin();

	bool inside = true;

	for ( ; elems != mmap->end(); elems++) {
		inside = true;

		if ( this->cDetector.getMousePosition().first < (*elems).getPosX()  ){
			inside = false;
		}

		if ( this->cDetector.getMousePosition().first > ((*elems).getPosX() + (ELEM_WIDTH * Screen::getInstance()->getLogic2PixelsFactor().first) ) ){
			inside = false;
		}

		if ( this->cDetector.getMousePosition().second < (*elems).getPosY() ){
			inside = false;
		}

		if ( this->cDetector.getMousePosition().second > ( (*elems).getPosY() + (ELEM_HEIGHT * Screen::getInstance()->getLogic2PixelsFactor().second) ) ){
			inside = false;
		}

		if (inside){
			std::cout << "clicked inside" << std::endl;
			return &(*elems);
		}


	}

	return NULL;
}



void GameController::handleEvents(){

	bool somethingHappened = false;
	bool mustCheck = false;
	bool save = false;
	bool changeBack = false;

	if ( this->cDetector.getState(MOUSE_LEFT_PRESSED) || this->cDetector.getState(MOUSE_RIGHT_PRESSED) ){
		mustCheck = true;
	}

	if (mustCheck && !this->currentElement && !this->currentMenuElement ){
		this->currentElement = this->checkInsideElements();
		this->currentMenuElement = this->checkInsideMenu();
		save = this->checkSaveRequested();
		changeBack = this->checkChangeBackground();

	}

	//this->cDetector.setLastMousePosition(this->cDetector.getMousePosition().first,this->cDetector.getMousePosition().second);

	if (this->currentElement){

		if ( this->cDetector.getState(MOUSE_LEFT_PRESSED) && this->cDetector.getState(MOUSE_MOVING) ){

			//Actualiza el elemView, el view loop dibuja el resto, notese que no actualizo la pos del objeto
			currentElement->setPosX( this->cDetector.getMousePosition().first - ((ELEM_WIDTH * Screen::getInstance()->getLogic2PixelsFactor().first)/2) );
			currentElement->setPosY( this->cDetector.getMousePosition().second - ((ELEM_HEIGHT * Screen::getInstance()->getLogic2PixelsFactor().second)/2) );
			this->cDetector.setState(MOUSE_MOVING,false);
			somethingHappened = true;
		}

		if ( this->cDetector.getState(MOUSE_RIGHT_PRESSED) && this->cDetector.getState(MOUSE_MOVING) && this->cDetector.changedRelPosition() ){
			// TODO hardcoded angle

			std::cout << "semovio rel: " << this->cDetector.getMouseRelativePosition().second << std::endl;
			std::cout << "Angulo: " << atan2(
					(float)(this->cDetector.getMousePosition().first - currentElement->getPosX()),
					(float)(this->cDetector.getMousePosition().second  - currentElement->getPosY()))
					* 180 / PI << std::endl;



			if ( this->cDetector.getMouseRelativePosition().second ){
				currentElement->setAngle( atan2(
						(float)(this->cDetector.getMousePosition().first - currentElement->getPosX()),
						(float)(this->cDetector.getMousePosition().second  - currentElement->getPosY()))
						* 180 / PI);


			}
			somethingHappened = true;
			this->cDetector.setState(MOUSE_MOVING,false);
		}

		if ( !this->cDetector.getState(MOUSE_LEFT_PRESSED) && !this->cDetector.getState(MOUSE_RIGHT_PRESSED) ){

			// std::cout << Screen::getInstance()->getLogic2PixelsFactor().first << ", " << Screen::getInstance()->getLogic2PixelsFactor().second << std::endl;
			if ( this->cLevel->checkMapPosition(this->cDetector.getMousePosition().first/Screen::getInstance()->getLogic2PixelsFactor().first,
												this->cDetector.getMousePosition().second/Screen::getInstance()->getLogic2PixelsFactor().second) ){
				// Guarda en el modelo
				this->cLevel->addEntity( GameElement((ElementType)currentElement->getType(),
													(this->cDetector.getMousePosition().first / Screen::getInstance()->getLogic2PixelsFactor().first),
													(this->cDetector.getMousePosition().second / Screen::getInstance()->getLogic2PixelsFactor().second),
													currentElement->getAngle() ) );
			}else{
				// Si es invalida elimina de game view y no se propaga al modelo
				this->gView->getElems()->remove(ElementView(currentElement));
				somethingHappened = true;
			}

			this->currentElement = NULL;
		}

	}else{
		if (this->currentMenuElement){
			if ( this->cDetector.getState(MOUSE_LEFT_PRESSED) && this->cDetector.getState(MOUSE_MOVING) ){
				currentMenuElement->setPosX( this->cDetector.getMousePosition().first - ((ELEM_WIDTH * Screen::getInstance()->getLogic2PixelsFactor().first)/2));
				currentMenuElement->setPosY( this->cDetector.getMousePosition().second - ((ELEM_HEIGHT * Screen::getInstance()->getLogic2PixelsFactor().second)/2) );
				this->cDetector.setState(MOUSE_MOVING,false);
				somethingHappened = true;
			}

			if ( !this->cDetector.getState(MOUSE_LEFT_PRESSED) && !this->cDetector.getState(MOUSE_RIGHT_PRESSED) ){

				// valida posicion en mapa
				if ( this->cLevel->checkMapPosition(this->cDetector.getMousePosition().first/Screen::getInstance()->getLogic2PixelsFactor().first,
													this->cDetector.getMousePosition().second/Screen::getInstance()->getLogic2PixelsFactor().second) ){
					// si es valida actualiza modelo
					this->cLevel->addEntity( GameElement((ElementType)currentMenuElement->getType(),
														(this->cDetector.getMousePosition().first / Screen::getInstance()->getLogic2PixelsFactor().first),
														(this->cDetector.getMousePosition().second / Screen::getInstance()->getLogic2PixelsFactor().second),
														currentMenuElement->getAngle() ) );

				}else{
					// Si es invalida elimina de game view y no se propaga al modelo
					this->gView->getElems()->pop_back();
					somethingHappened = true;
				}


				this->currentMenuElement = NULL;
			}

		}else
			this->cDetector.clearStates();
	}

	if (save){
		std::cout << "TODO: persistir modelo a YAML" << std::endl;
	}

	if(changeBack){
		//TODO: Hardcoded default image path
		std::string back = "../TIM_tallerv1/image/";
		std::cout << "Changed background to: " << back.append(this->cDetector.getBackgroundText()) << std::endl;

		Sprites::getInstance()->addSprite(4,back);
		somethingHappened = true;

	}

	if ( this->cDetector.getBackgroundText() != "" ){
		this->gView->drawInputText(this->cDetector.getBackgroundText());
		somethingHappened = true;
	}

	this->changes = somethingHappened;
}



ElementView* GameController::checkInsideMenu(){

	bool inside = true;

	// TODO MAX MENU ELEMS
	for ( int i=0; i < 4 ; i++) {
		inside = true;

		if ( ( this->cDetector.getMousePosition().first < (Screen::getInstance()->getWidth() - MENU_WIDTH + ALIGN_SPRITE) ) ||
				(this->cDetector.getMousePosition().first > (Screen::getInstance()->getWidth() - MENU_WIDTH + ALIGN_SPRITE + SPRITES_WIDTH))){
			inside = false;
		}

		if ( ( this->cDetector.getMousePosition().second < (ARROW_Y_POS + ((ARROW_Y_POS + SPRITES_HEIGHT)*(i+1))) ) ||
				(this->cDetector.getMousePosition().second > ( (ARROW_Y_POS + ((ARROW_Y_POS + SPRITES_HEIGHT)*(i+1))) + SPRITES_HEIGHT)) ){
			inside = false;
		}

		if (inside){
			std::cout << "clicked inside menu" << std::endl;
			this->gView->addElement(i,this->cDetector.getMousePosition().first,this->cDetector.getMousePosition().second,0);

			return &this->gView->getElems()->back();
		}


	}

	return NULL;
}


bool GameController::getChanges(){
	return this->changes;
}



bool GameController::checkSaveRequested(){

	bool inside = true;

	if ( this->cDetector.getMousePosition().first < (Screen::getInstance()->getWidth() - MENU_WIDTH - 160 + 15)  ){
		inside = false;
	}

	if ( this->cDetector.getMousePosition().first > (Screen::getInstance()->getWidth() - MENU_WIDTH - 160 + 15 + SPRITES_WIDTH) ){
		inside = false;
	}

	if ( this->cDetector.getMousePosition().second < (Screen::getInstance()->getHeight() - SPRITES_HEIGHT - ARROW_Y_POS) ){
		inside = false;
	}

	if ( this->cDetector.getMousePosition().second > (Screen::getInstance()->getHeight() - ARROW_Y_POS ) ){
		inside = false;
	}

	return inside;

}


bool GameController::checkChangeBackground(){

	bool inside = true;

	if ( this->cDetector.getMousePosition().first < (Screen::getInstance()->getWidth() - MENU_WIDTH - 160 + 30 + SPRITES_WIDTH)  ){
		inside = false;
	}

	if ( this->cDetector.getMousePosition().first > (Screen::getInstance()->getWidth() - MENU_WIDTH - 160 + 30 + SPRITES_WIDTH + SPRITES_WIDTH) ){
		inside = false;
	}

	if ( this->cDetector.getMousePosition().second < (Screen::getInstance()->getHeight() - SPRITES_HEIGHT - ARROW_Y_POS) ){
		inside = false;
	}

	if ( this->cDetector.getMousePosition().second > (Screen::getInstance()->getHeight() - ARROW_Y_POS ) ){
		inside = false;
	}

	return inside;

}


