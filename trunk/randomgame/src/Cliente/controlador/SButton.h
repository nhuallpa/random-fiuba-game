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
};

#endif /*__SBUTTON__*/