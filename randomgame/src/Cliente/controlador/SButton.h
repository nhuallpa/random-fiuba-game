#pragma once

#ifndef __SBUTTON__
#define __SBUTTON__

#include "GameButton.h"


class SButton : public GameButton
{
public:
	SButton(void);
	~SButton(void);
	void execute(const Uint8* keys);
	bool isBeginLife();
	bool isRegenerateWorld();
	void cleanState();

private:
	enum ButtonState{BUTTON_PUSH, BUTTON_POP};
	enum PreviousAction{BEGIN_LIFE, REGENERATE_WORLD};
	ButtonState buttonState;
	PreviousAction prevAction;
};

#endif /*__SBUTTON__*/