#include "PButton.h"

using namespace std;

PButton::PButton(void)
{
	m_state = BUTTON_POP;
}


PButton::~PButton(void)
{
}


void PButton::execute(const Uint8* keys){
	if(keys[SDL_SCANCODE_P]){
		m_state = BUTTON_PUSH;
	}
	else{
		m_state = BUTTON_POP;
	}
	return;
}
