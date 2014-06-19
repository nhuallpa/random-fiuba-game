#pragma once

#ifndef __SHEEP_VIEW_H__
#define __SHEEP_VIEW_H__

#include "..\ProjectileView.h"


class SheepView: public ProjectileView
{

public:
	SheepView(int id);
									
	void clean();
	
	void update();

	void draw(SDLScreen & screen);

	void detonate();

	~SheepView(void);

};

#endif /** __GRENADE_VIEW_H__ **/