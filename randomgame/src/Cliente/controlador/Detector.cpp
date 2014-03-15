/*
 * Detector.cpp
 *
 *  Created on: 09/09/2013
 *      Author: ALiguori
 */

#include "Detector.h"

using namespace std;

Detector::Detector() {
	this->backgroundText = "";
	this->changedPosition = false;
}

Detector::~Detector() {
}

void Detector::detect(){

	SDL_StartTextInput();
	SDL_Event* ev = new SDL_Event();
	while( SDL_PollEvent( ev ) != 0 )
	{
		this->handleEvents(ev);
	}
}


bool Detector::changedRelPosition(){
	return this->changedPosition;
}

void Detector::handleEvents(SDL_Event* e){

	this->mousePosition = make_pair(e->motion.x,e->motion.y);
	this->changedPosition = false;
	if ( this->mouseRelativePosition.second != e->motion.yrel ){
		this->mouseRelativePosition = make_pair(e->motion.xrel,e->motion.yrel);
		this->changedPosition = true;
	}
	this->cState[INPUT_TXT_CHGD] = false;

	if( e->type == SDL_WINDOWEVENT )
	{
			std::cout << "new w: " << Screen::getInstance()->getWidth()  << std::endl;
			std::cout << "event: " <<  e->window.data1  << std::endl;
			std::cout << "I expect: " <<  SDL_WINDOWEVENT_SIZE_CHANGED << std::endl;

			if( e->window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
			{
			//Get new dimensions and repaint on window size change
			// Ideally I need to re-call a controller (lets say Screen Controller)
				Screen::getInstance()->setWidth( e->window.data1 );
				Screen::getInstance()->setHeight( e->window.data2 );
				// TODO @LOG - changed size
				//std::cout << "new w: " << Screen::getInstance()->getWidth()  << std::endl;
				//std::cout << "new h: " << Screen::getInstance()->getHeight()  << std::endl;
				SDL_RenderPresent( Screen::getInstance()->getRenderer() );
			}

				//Repaint on exposure
				if( e->window.event ==  SDL_WINDOWEVENT_EXPOSED){
				SDL_RenderPresent( Screen::getInstance()->getRenderer() );
				}

				//Mouse entered window
				if( e->window.event ==  SDL_WINDOWEVENT_ENTER){
				Screen::getInstance()->setMouseFocus(true);
				}

				//Mouse left window
				if( e->window.event ==  SDL_WINDOWEVENT_LEAVE){
				Screen::getInstance()->setMouseFocus(false);
				}

				//Window has keyboard focus
				if( e->window.event ==  SDL_WINDOWEVENT_FOCUS_GAINED){
				Screen::getInstance()->setKeyboardFocus(true);
				}

				//Window lost keyboard focus
				if( e->window.event ==  SDL_WINDOWEVENT_FOCUS_LOST){
				Screen::getInstance()->setKeyboardFocus(false);
				}
	}
	switch( e->type )
	{
		case SDL_MOUSEMOTION:
			this->cState[MOUSE_MOVING] = true;
			break;
		case SDL_QUIT:
			this->cState[EXIT_REQUEST] = true;
			break;

		case SDL_MOUSEBUTTONUP:
			if (e->button.button == SDL_BUTTON_LEFT){
				this->cState[MOUSE_LEFT_PRESSED] = false;
				this->cState[MOUSE_MOVING] = false;
			}else{
				this->cState[MOUSE_RIGHT_PRESSED] = false;
				this->cState[MOUSE_MOVING] = false;
			}
			break;

		case SDL_MOUSEBUTTONDOWN:
			if (e->button.button == SDL_BUTTON_LEFT){
				//Si estaba apretado el otro libero los dos
				if ( this->cState[MOUSE_RIGHT_PRESSED] ){
					this->cState[MOUSE_LEFT_PRESSED] = false;
					this->cState[MOUSE_RIGHT_PRESSED] = false;
					this->cState[MOUSE_MOVING] = false;
					break;
				}
				this->cState[MOUSE_LEFT_PRESSED] = true;
				this->cState[MOUSE_MOVING] = false;
			}else{
				//Si estaba apretado el otro libero los dos
				if ( this->cState[MOUSE_LEFT_PRESSED] ){
					this->cState[MOUSE_LEFT_PRESSED] = false;
					this->cState[MOUSE_RIGHT_PRESSED] = false;
					this->cState[MOUSE_MOVING] = false;
					break;
				}
				this->cState[MOUSE_RIGHT_PRESSED] = true;
				this->cState[MOUSE_MOVING] = false;
			}
			break;

		case SDL_KEYDOWN:
			//Handle backspace
			if( e->key.keysym.sym == SDLK_BACKSPACE && this->backgroundText.length() > 0 )
			{
				//lop off character
				this->backgroundText.pop_back();
				this->cState[INPUT_TXT_CHGD] = true;
			}else if( e->key.keysym.sym == SDLK_v && (SDL_GetModState() & KMOD_CTRL) )
			{
				// Accion ctrl+v = pegar
				this->backgroundText = SDL_GetClipboardText();
				this->cState[INPUT_TXT_CHGD] = true;
			}
			break;

		case SDL_TEXTINPUT:
			//Not pasting
			if( !( ( e->text.text[ 0 ] == 'v' || e->text.text[ 0 ] == 'V' ) && (SDL_GetModState() & KMOD_CTRL) ) )
			{
				//Append character
				this->backgroundText += e->text.text;
				this->cState[INPUT_TXT_CHGD] = true;
			}
			break;
	}

	const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );
	if (currentKeyStates[ SDL_SCANCODE_LSHIFT ] ){
		this->cState[KB_SHIFT_PRESSED] = true;
	}else
		this->cState[KB_SHIFT_PRESSED] = false;


	//delay over detecting events
	SDL_Delay(5);

}


std::string Detector::getBackgroundText(){
	return this->backgroundText;

}

void Detector::clearMousePosition(){
	this->mousePosition = make_pair(0,0);
	this->mouseRelativePosition = make_pair(0,0);
}

std::pair<int,int> Detector::getMousePosition(){
	return this->mousePosition;
}


std::pair<int,int> Detector::getMouseRelativePosition(){
	return this->mouseRelativePosition;
}


bool Detector::getState(State action){
	return this->cState[action];
}


void Detector::clearStates(){
	for (int i=0; i <= TOTAL_STATES; i++){
		this->cState[i] = false;
	}
}

void Detector::setState(State action, bool value){
	this->cState[action] = value;
}

void Detector::setLastMousePosition(int x, int y){
	this->lastMousePosition = std::make_pair(x,y);
}

std::pair<int,int> Detector::getLastMousePosition(){
	return this->lastMousePosition;
}
