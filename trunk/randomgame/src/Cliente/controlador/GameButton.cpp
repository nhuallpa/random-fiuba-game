#include "GameButton.h"
#include <exception>

GameButton::GameButton(void)
{
}


GameButton::~GameButton(void)
{
}

void GameButton::execute(const Uint8* keys) 
	throw (int, std::bad_exception){
	throw (1,"Method not implmented");
}

bool GameButton::getPush(bState state) {
	return (m_state == state);
}
