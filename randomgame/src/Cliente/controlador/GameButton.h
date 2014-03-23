#pragma once

#ifndef __GAMEBUTTON__
#define __GAMEBUTTON__

#include <SDL.h>



class GameButton
{
public:
	GameButton(void);
	~GameButton(void);
	virtual void execute(const Uint8* keys);
	virtual void cleanState();
};

#endif /*__GAMEBUTTON__*/