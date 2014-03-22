#include "SButton.h"

using namespace std;

SButton::SButton(void)
{
	m_state = BUTTON_POP;
}


SButton::~SButton(void)
{
}

void SButton::execute(const Uint8* keys){
	if(keys[SDL_SCANCODE_S]){
		m_state = BUTTON_PUSH;
	}
	else{
		m_state = BUTTON_POP;
	}
	return;
}