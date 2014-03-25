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

float nearest2(float f){
	return floorf(f * 100 + 0.5) / 100; 
}


GameController::GameController() {
	gView = NULL;
	currentElement = NULL;
	currentMenuElement = NULL;
	cLevel  = NULL;
	changes = false;

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
		
		this->gView->addElement(((*elems).second).getType(),
				(((*elems).first).first * Screen::getInstance()->getLogic2PixelsFactor().first) - ((ELEM_WIDTH * Screen::getInstance()->getLogic2PixelsFactor().first)/2.0) ,
				(((*elems).first).second * Screen::getInstance()->getLogic2PixelsFactor().second) - ((ELEM_HEIGHT * Screen::getInstance()->getLogic2PixelsFactor().second)/2.0),
				((*elems).second).getRotation());
	}


	return true;
}

void GameController::detectEvents(){
	this->cDetector.detect();
}


ElementView* GameController::checkInsideElements(){
	/*
	std::list<ElementView>* mmap = this->gView->getElems();
	std::list<ElementView>::reverse_iterator elems = mmap->rbegin();

	bool inside = true;

	for ( ; elems != mmap->rend(); ++elems) {
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

			bool alpha = false;
			float x = ( ( ( (this->cDetector.getMousePosition().first - (*elems).getPosX()) )) * cos(( (*elems).getAngle())*PI/180 ) ) 
					  - ( ( (this->cDetector.getMousePosition().second - (*elems).getPosY())) * sin((180+(*elems).getAngle())*PI/180 ));
			
			float y = (-1)*( (  (this->cDetector.getMousePosition().first - (*elems).getPosX())) * sin( ( (*elems).getAngle() ) * PI/180 ) )
					  + ( ((this->cDetector.getMousePosition().second - (*elems).getPosY()) ) * cos(( (*elems).getAngle())*PI/180 ));


			if ( x < 0) x+=48;
			if ( y < 0) y+=48;

			//std::cout << "sin: " << sin(( (*elems).getAngle())*PI/180 ) << ", cos: " << cos(( (*elems).getAngle())*PI/180 ) << std::endl;
			//std::cout << "pos x: " << x << ", pos y:" << y << ", angle: " << (*elems).getAngle() << ", Height: " << (*elems).getHeight() << std::endl;
			alpha = Sprites::getInstance()->getSprite((*elems).getType())->isAlphaPixel( x,y);	
			if ( !alpha)
				return &(*elems);
		}
	}*/
	return NULL;
}


bool GameController::handleEvents(){

	/*
	if ( this->cDetector.getState(EXIT_REQUEST) ){
		return true;
	}


	if (this->cDetector.getState(WNDW_SIZE_CHGD)){
		this->updateElements();
	}

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
		if (this->currentElement){
			//std::cout << "en pos" << (currentElement->getPosX()/ Screen::getInstance()->getLogic2PixelsFactor().first)+ (ELEM_WIDTH * Screen::getInstance()->getLogic2PixelsFactor().first)/2 <<
			//		", y: " << (currentElement->getPosY() /Screen::getInstance()->getLogic2PixelsFactor().second)+ (ELEM_HEIGHT * Screen::getInstance()->getLogic2PixelsFactor().second)/2 << std::endl;
	this->lastElemPos = std::make_pair(	nearest2((currentElement->getPosX()+ ((ELEM_WIDTH * Screen::getInstance()->getLogic2PixelsFactor().first)/2))/ Screen::getInstance()->getLogic2PixelsFactor().first),
		nearest2((currentElement->getPosY() + ((ELEM_HEIGHT * Screen::getInstance()->getLogic2PixelsFactor().second))/2)/Screen::getInstance()->getLogic2PixelsFactor().second));

	//std::cout << "dentro de: " << this->lastElemPos.first << ", " << this->lastElemPos.second << std::endl;
		}

	}



	if (this->currentElement){

		ElementView copy = new ElementView(this->currentElement);
		//memcpy((void*)&copy,*(this->currentElement),sizeof(*(this->currentElement)));
		this->gView->removeElement(*(this->currentElement));
		this->gView->addElement(copy);
		this->currentElement = &this->gView->getElems()->back();

		if ( this->cDetector.getState(MOUSE_LEFT_PRESSED) && this->cDetector.getState(MOUSE_MOVING) ){

			//Actualiza el elemView, el view loop dibuja el resto, notese que no actualizo la pos del objeto

			currentElement->setPosX( this->cDetector.getMousePosition().first - ((ELEM_WIDTH * Screen::getInstance()->getLogic2PixelsFactor().first)/2) );
			currentElement->setPosY( this->cDetector.getMousePosition().second - ((ELEM_HEIGHT * Screen::getInstance()->getLogic2PixelsFactor().second)/2) );

			this->cDetector.setState(MOUSE_MOVING,false);
			somethingHappened = true;
		}

		if ( this->cDetector.getState(MOUSE_RIGHT_PRESSED) && this->cDetector.getState(MOUSE_MOVING) && this->cDetector.changedRelPosition() ){
			if ( this->cDetector.getMouseRelativePosition().second ){

				//std::cout << "1) Angle: " << currentElement->getAngle() << std::endl;
				float angle = (atan2(
						(float)(this->cDetector.getMousePosition().first - currentElement->getPosX()),
						(float)( -1*(this->cDetector.getMousePosition().second  - currentElement->getPosY()) ))
						* 180 / PI);
				if ( angle > 0){
					currentElement->setAngle(angle);
				}else{
					angle = angle + 360;
					currentElement->setAngle(angle);
				}

				//std::cout << "2) Angle: " << currentElement->getAngle() << std::endl;


			}
			somethingHappened = true;
			this->cDetector.setState(MOUSE_MOVING,false);
		}

		if ( this->cDetector.getState(MOUSE_LEFT_PRESSED) && this->cDetector.getState(KB_SHIFT_PRESSED)){


			//Elimino del modelo
			//std::cout << "elimino: " << nearest2((currentElement->getPosX() + ((ELEM_WIDTH * Screen::getInstance()->getLogic2PixelsFactor().first)/2.0)) / Screen::getInstance()->getLogic2PixelsFactor().first) << 
			//	", " << nearest2((currentElement->getPosY() + ((ELEM_HEIGHT * Screen::getInstance()->getLogic2PixelsFactor().second)/2.0))/Screen::getInstance()->getLogic2PixelsFactor().second) << std::endl;
			this->cLevel->removeEntity(std::make_pair(	nearest2((currentElement->getPosX() + ((ELEM_WIDTH * Screen::getInstance()->getLogic2PixelsFactor().first)/2)) / Screen::getInstance()->getLogic2PixelsFactor().first),
														nearest2((currentElement->getPosY() + ((ELEM_HEIGHT * Screen::getInstance()->getLogic2PixelsFactor().second)/2))/Screen::getInstance()->getLogic2PixelsFactor().second) ) );

			//Elimino de la vista
			this->gView->getElems()->remove(ElementView(currentElement));

			this->cDetector.setState(KB_SHIFT_PRESSED,false);
			this->currentElement = NULL;
		}

		if ( !this->cDetector.getState(MOUSE_LEFT_PRESSED) && !this->cDetector.getState(MOUSE_RIGHT_PRESSED) ){

			//std::cout << "Factor: " << Screen::getInstance()->getLogic2PixelsFactor().first << ", " << Screen::getInstance()->getLogic2PixelsFactor().second << std::endl;
			if ( this->cLevel->checkMapPosition((currentElement->getPosX() + ((ELEM_WIDTH * Screen::getInstance()->getLogic2PixelsFactor().first)/2))
												/ Screen::getInstance()->getLogic2PixelsFactor().first,
												(currentElement->getPosY() + ((ELEM_HEIGHT * Screen::getInstance()->getLogic2PixelsFactor().second)/2))
												/Screen::getInstance()->getLogic2PixelsFactor().second) ){
				// Guarda en el modelo
				//std::cout << "guardo en el modelo y borro " << this->lastElemPos.first << ", " << this->lastElemPos.second << std::endl;
				this->cLevel->removeEntity(this->lastElemPos);

				this->cLevel->addEntity( GameElement(currentElement->getType(),
										nearest2((currentElement->getPosX() + ((ELEM_WIDTH * Screen::getInstance()->getLogic2PixelsFactor().first)/2)) / Screen::getInstance()->getLogic2PixelsFactor().first),
										nearest2((currentElement->getPosY() + ((ELEM_HEIGHT * Screen::getInstance()->getLogic2PixelsFactor().second)/2)) /Screen::getInstance()->getLogic2PixelsFactor().second),
										currentElement->getAngle() ) );

			}else{
				// Si es invalida elimina de game view y no se propaga al modelo
				//this->cLevel->removeEntity(this->lastElemPos);
				this->cLevel->removeEntity(this->lastElemPos );
				this->gView->getElems()->remove(ElementView(currentElement));
				somethingHappened = true;
			}

			this->currentElement = NULL;
		}

	}else{
		if (this->currentMenuElement){
			//std::cout << "pressed: " << this->cDetector.getState(MOUSE_LEFT_PRESSED) << ", moving: " << this->cDetector.getState(MOUSE_MOVING)<< std::endl;
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
					this->cLevel->addEntity( GameElement(currentMenuElement->getType(),
														nearest2((this->cDetector.getMousePosition().first ) / Screen::getInstance()->getLogic2PixelsFactor().first),
														nearest2((this->cDetector.getMousePosition().second) / Screen::getInstance()->getLogic2PixelsFactor().second),
														currentMenuElement->getAngle() ) );

				}else{
					// Si es invalida elimina de game view y no se propaga al modelo
					this->gView->getElems()->pop_back();
					somethingHappened = true;
				}
				this->currentMenuElement = NULL;
			}

		}else{

			if ( this->cDetector.getState(MOUSE_LEFT_PRESSED) ){
				if (this->checkExitRequested()){
					return true;
				}

				if (this->checkMoveDownRequested()){
					this->gView->moveMenuDown();
				}

				if (this->checkMoveUpRequested()){
					this->gView->moveMenuUp();
				}
			}

			if ( this->cDetector.getState(KB_UP_ARROW)){
				this->gView->moveMenuUp();
				this->cDetector.setState(KB_UP_ARROW,false);
			}

			if ( this->cDetector.getState(KB_DOWN_ARROW)){
				this->gView->moveMenuDown();
				this->cDetector.setState(KB_DOWN_ARROW,false);
			}

			if ( this->cDetector.getState(KB_ENTER_PRESSED)){
				changeBack=true;
				this->cDetector.setState(KB_ENTER_PRESSED,false);
			}

			this->cDetector.clearStates();

		}
	}

	if (save){
		this->persist();
	}

	if(changeBack){
		//TODO: Hardcoded default image path
		std::string back = "image/";
		back.append(this->cDetector.getBackgroundText());
		//Sprites::getInstance()->addSprite( Sprites::getInstance()->getSpriteMap()->size()-5 ,back);
		this->gView->loadBackground(Sprites::getInstance()->getSpriteMap()->size()-5 ,back);
		somethingHappened = true;

	}

	if ( this->cDetector.getBackgroundText() != "" ){
		this->gView->drawInputText(this->cDetector.getBackgroundText());
		somethingHappened = true;
	}else{
		this->gView->drawInputText("");
		somethingHappened = true;
	}

	this->changes = somethingHappened;
	*/

	return false;
}



ElementView* GameController::checkInsideMenu(){

	bool inside = true;

	/*
	int qtyMenuElems = Screen::getInstance()->getHeight() / (ARROW_Y_POS + ARROW_Y_POS + SPRITES_HEIGHT);

	if ( qtyMenuElems > (Sprites::getInstance()->getSpriteMap()->size()-CONFIG_IMAGES) ){
		qtyMenuElems = Sprites::getInstance()->getSpriteMap()->size()-CONFIG_IMAGES;
	}


	for ( int i=0; i < qtyMenuElems ; i++) {
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
			
			this->gView->addElement( (i + this->gView->getMenuOffset())%(Sprites::getInstance()->getSpriteMap()->size()-CONFIG_IMAGES),
									this->cDetector.getMousePosition().first,
									this->cDetector.getMousePosition().second,
									0);
			return &this->gView->getElems()->back();
		}


	}
	*/
	return NULL;
}


bool GameController::getChanges(){
	return this->changes;
}



bool GameController::checkSaveRequested(){
	
	bool inside = true;
	/*
	if ( this->cDetector.getMousePosition().first < (Screen::getInstance()->getWidth() - MENU_WIDTH - (SPRITES_WIDTH*2) -(15*2))  ){
		inside = false;
	}

	if ( this->cDetector.getMousePosition().first > (Screen::getInstance()->getWidth() - MENU_WIDTH - SPRITES_WIDTH -(15*2)) ){
		inside = false;
	}

	if ( this->cDetector.getMousePosition().second < (Screen::getInstance()->getHeight() - SPRITES_HEIGHT - ARROW_Y_POS) ){
		inside = false;
	}

	if ( this->cDetector.getMousePosition().second > (Screen::getInstance()->getHeight() - ARROW_Y_POS ) ){
		inside = false;
	}
	*/
	return inside;

}


bool GameController::checkChangeBackground(){
	
	bool inside = true;
	/*
	if ( this->cDetector.getMousePosition().first < (Screen::getInstance()->getWidth() - MENU_WIDTH - SPRITES_WIDTH - 15)  ){
		inside = false;
	}

	if ( this->cDetector.getMousePosition().first > (Screen::getInstance()->getWidth() - MENU_WIDTH - 15) ){
		inside = false;
	}

	if ( this->cDetector.getMousePosition().second < (Screen::getInstance()->getHeight() - SPRITES_HEIGHT - ARROW_Y_POS) ){
		inside = false;
	}

	if ( this->cDetector.getMousePosition().second > (Screen::getInstance()->getHeight() - ARROW_Y_POS ) ){
		inside = false;
	}
	*/
	return inside;

}

bool GameController::checkExitRequested(){

	bool inside = true;
	/*
	if ( this->cDetector.getMousePosition().first < (Screen::getInstance()->getWidth() - MENU_WIDTH - (SPRITES_WIDTH*3) -(15*3))  ){
		inside = false;
	}

	if ( this->cDetector.getMousePosition().first > (Screen::getInstance()->getWidth() - MENU_WIDTH - (SPRITES_WIDTH*2) -(15*3)) ){
		inside = false;
	}

	if ( this->cDetector.getMousePosition().second < (Screen::getInstance()->getHeight() - SPRITES_HEIGHT - ARROW_Y_POS) ){
		inside = false;
	}

	if ( this->cDetector.getMousePosition().second > (Screen::getInstance()->getHeight() - ARROW_Y_POS ) ){
		inside = false;
	}
	*/
	return inside;

}

bool GameController::checkMoveUpRequested(){

	bool inside = true;
	/*
	if ( this->cDetector.getMousePosition().first < (Screen::getInstance()->getWidth() - MENU_WIDTH + ALIGN_SPRITE)  ){
		inside = false;
	}

	if ( this->cDetector.getMousePosition().first > (Screen::getInstance()->getWidth() - MENU_WIDTH + ALIGN_SPRITE + SPRITES_WIDTH) ){
		inside = false;
	}

	if ( this->cDetector.getMousePosition().second < ARROW_Y_POS ){
		inside = false;
	}

	if ( this->cDetector.getMousePosition().second > (SPRITES_HEIGHT + ARROW_Y_POS ) ){
		inside = false;
	}
	*/
	return inside;

}

bool GameController::checkMoveDownRequested(){

	bool inside = true;
	/*
	if ( this->cDetector.getMousePosition().first < (Screen::getInstance()->getWidth() - MENU_WIDTH + ALIGN_SPRITE)  ){
		inside = false;
	}

	if ( this->cDetector.getMousePosition().first > (Screen::getInstance()->getWidth() - MENU_WIDTH + ALIGN_SPRITE + SPRITES_WIDTH) ){
		inside = false;
	}

	if ( this->cDetector.getMousePosition().second < (Screen::getInstance()->getHeight() - SPRITES_HEIGHT - ARROW_Y_POS) ){
		inside = false;
	}

	if ( this->cDetector.getMousePosition().second > (Screen::getInstance()->getHeight() - ARROW_Y_POS ) ){
		inside = false;
	}
	*/
	return inside;

}

std::string toString(int n){
	std::stringstream ss;
	ss << n;
	return ss.str();
}

std::string float2String(float n){
	std::stringstream ss;
	ss << n;
	return ss.str();
}


void GameController::persist(){
	//Todo: arreglar persistencia controlador
	//PersistYaml* aPersist=PersistYaml::getInstance();
	//ParserYaml* aParser = ParserYaml::getInstance();
	//std::multimap<std::pair<float, float>, GameElement> mmap = this->cLevel->getEntities();
	//std::multimap<std::pair<float, float>, GameElement>::iterator elems = mmap.begin();

	//aPersist->setNivelNombre( Screen::getInstance()->getScreenName() );
	//aPersist->setNivelFondo( this->gView->getBackground() );
	//aPersist->setNivelAlto( toString(Screen::getInstance()->getHeight()) );
	//aPersist->setNivelAncho( toString(Screen::getInstance()->getWidth()) );

	//for ( int i=0; elems != mmap.end(); elems++,i++) {
	//	//((*elems).first).first; //x - up left corner
	//	//((*elems).first).second; //y - up left corner
	//	//((*elems).second).getType(); // elem type
	//	//((*elems).second).getRotation(); // rotation
	//	//(int type, int posX, int posY, int degree);
	//	//std::cout << "elem: " <<i<<std::endl;
	//	aPersist->setElem(	aParser->getElementType( ((*elems).second).getType()) ,
	//					float2String( ((*elems).first).first ),
	//					float2String( ((*elems).first).second ),
	//					toString( (int)((*elems).second).getRotation()) );	
	//}

	//aPersist->escribirYaml(aParser->getLevelFilePath());
}

void GameController::updateElements(){
	/*
	std::list<ElementView>* mmap = this->gView->getElems();
	std::list<ElementView>::iterator elems = mmap->begin();

	for ( ; elems != mmap->end(); elems++ ) {

		(*elems).setPosX( (*elems).getPosX() / Screen::getInstance()->getLastLogic2PixelsFactor().first * Screen::getInstance()->getLogic2PixelsFactor().first);
		(*elems).setPosY( (*elems).getPosY() / Screen::getInstance()->getLastLogic2PixelsFactor().second * Screen::getInstance()->getLogic2PixelsFactor().second);
	}

	this->cDetector.setState(WNDW_SIZE_CHGD,false);
	*/
}

