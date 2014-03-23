#include "SButton.h"

using namespace std;

SButton::SButton(void)
{
	buttonState = BUTTON_POP;
	prevAction = REGENERATE_WORLD;
}


SButton::~SButton(void)
{
}

void SButton::execute(const Uint8* keys){
	if(keys[SDL_SCANCODE_S]){
		buttonState = BUTTON_PUSH;
	}
	else{
		buttonState = BUTTON_POP;
	}
	return;
}

bool SButton::isBeginLife(){
	return  ((prevAction == REGENERATE_WORLD)
		  && (buttonState == BUTTON_PUSH));
}

bool SButton::isRegenerateWorld(){
	return  ((prevAction == BEGIN_LIFE)
		  && (buttonState == BUTTON_PUSH));
}

void SButton::cleanState(){
	if(buttonState == BUTTON_PUSH){	
		if(prevAction == REGENERATE_WORLD){
			prevAction = BEGIN_LIFE;
		}
		else{
			prevAction = REGENERATE_WORLD;
		}
	}
	buttonState = BUTTON_POP;
}
