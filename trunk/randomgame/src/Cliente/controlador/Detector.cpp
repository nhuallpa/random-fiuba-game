/*
 * Detector.cpp
 *
 *  Created on: 09/09/2013
 *      Author: ALiguori
 */

#include "Detector.h"
#include "../../utils/Log.h"

using namespace std;

Detector::Detector() {
	this->backgroundText = "";
	this->changedPosition = false;
	this->clearStates();
}

Detector::~Detector() {
}

void Detector::detect(){

	SDL_StartTextInput();
	SDL_Event* ev = new SDL_Event();
	while( SDL_PollEvent( ev ) != 0 )
	{
		if ( ev->type == SDL_QUIT){
			this->cState[EXIT_REQUEST] = true;
			return;
		}
		this->handleEvents(ev);
	}
	free(ev);
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
			if( e->window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
			{
			//Get new dimensions and repaint on window size change
			// Ideally I need to re-call a controller (lets say Screen Controller)
				Screen::getInstance()->updateLastFactor();
				Screen::getInstance()->setWidth( e->window.data1 );
				Screen::getInstance()->setHeight( e->window.data2 );
				this->cState[WNDW_SIZE_CHGD] = true;

				// TODO @LOG - changed size
				Log::d("Changed size width:%d, height:%d",Screen::getInstance()->getWidth(),Screen::getInstance()->getHeight());
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

			if (e->button.button == 4)
				this->cState[KB_UP_ARROW] = true;
			if (e->button.button == 5 )
				this->cState[KB_DOWN_ARROW] = true;

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

				if (e->button.button == 4 )
					this->cState[KB_UP_ARROW] = true;
				if (e->button.button == 5 )
					this->cState[KB_DOWN_ARROW] = true;

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

		case SDL_MOUSEWHEEL:
			if ( e->wheel.y > 0 ){
				this->cState[KB_UP_ARROW] = true;
			}
			if ( e->wheel.y < 0 ){
				this->cState[KB_DOWN_ARROW] = true;
			}

			break;

		case SDL_KEYDOWN:
			//borrar
			if( e->key.keysym.sym == SDLK_BACKSPACE && this->backgroundText.length() > 0 )
			{
				if ( this->backgroundText.length() == 1 ){
					this->backgroundText = "";
				}else
					this->backgroundText = this->backgroundText.substr(0,this->backgroundText.length()-1);

				this->cState[INPUT_TXT_CHGD] = true;
			}else if( e->key.keysym.sym == SDLK_v && (SDL_GetModState() & KMOD_CTRL) )
			{
				// Accion ctrl+v = pegar
				this->backgroundText = SDL_GetClipboardText();
				this->cState[INPUT_TXT_CHGD] = true;
			}
			break;

		case SDL_TEXTINPUT:
			if( !( ( e->text.text[ 0 ] == 'v' || e->text.text[ 0 ] == 'V' ) && (SDL_GetModState() & KMOD_CTRL) ) )
			{
				this->backgroundText += e->text.text;
				this->cState[INPUT_TXT_CHGD] = true;
			}
			break;
	}

	const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );
	if (currentKeyStates[ SDL_SCANCODE_LSHIFT ] ){
		this->cState[KB_SHIFT_PRESSED] = true;
	}

	if (currentKeyStates[ SDL_SCANCODE_DOWN ] ){
		this->cState[KB_DOWN_ARROW] = true;
	}
	
	if (currentKeyStates[ SDL_SCANCODE_RETURN ] ){
		this->cState[KB_ENTER_PRESSED] = true;
	}

	if (currentKeyStates[ SDL_SCANCODE_UP ] ){
		this->cState[KB_UP_ARROW] = true;
	}
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
