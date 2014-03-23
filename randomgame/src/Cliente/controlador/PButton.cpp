#include "PButton.h"

using namespace std;

PButton::PButton(void)
{
	pause = false;
}


PButton::~PButton(void)
{
}


void PButton::execute(const Uint8* keys){
	if(keys[SDL_SCANCODE_P]){
		if(!pause){
			pause = true;
		}
		else{
			pause = false;
		}
	}
}

bool PButton::isPause(){
	return pause;
}

void PButton::cleanState(){
	return;
}


