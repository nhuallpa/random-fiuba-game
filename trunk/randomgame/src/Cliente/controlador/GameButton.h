#pragma once

#ifndef __GAMEBUTTON__
#define __GAMEBUTTON__

#include <SDL.h>

	enum bState{BUTTON_PUSH, BUTTON_POP};

class GameButton
{
public:
	GameButton(void);
	~GameButton(void);
	virtual void execute(const Uint8* keys);
	bool getPush(bState state);
protected:
	bState m_state;
};

#endif /*__GAMEBUTTON__*/