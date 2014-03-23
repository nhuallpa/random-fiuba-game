#pragma once

#ifndef __PBUTTON__
#define __PBUTTON__

#include "GameButton.h"
class PButton : public GameButton
{
public:
	PButton(void);
	~PButton(void);
	void execute(const Uint8* keys);
	bool isPause();
	void cleanState();
private:
	bool pause;
};

#endif /*__PBUTTON__*/

