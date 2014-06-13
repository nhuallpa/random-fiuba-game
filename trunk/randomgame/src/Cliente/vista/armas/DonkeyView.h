#pragma once

#ifndef __DONKEY_VIEW_H__
#define __DONKEY_VIEW_H__

#include "..\ProjectileView.h"


class DonkeyView: public ProjectileView
{

public:
	DonkeyView(int id);
									
	void clean();
	
	void update();

	void draw(SDLScreen & screen);

	void detonate();

	~DonkeyView(void);

};

#endif /** __DONKEY_VIEW_H__ **/