#pragma once

#ifndef __VIEW_GROUP_H__
#define __VIEW_GROUP_H__
#include <list>
#include "View.h"
class ViewGroup : 	public View
{
private:

	std::list<View*> views;

public:
	ViewGroup(int x, int y, int width, int height);

	void add(View* aView);

	void clean();
	
	void update();
	
	void draw(SDLScreen & screen);

	~ViewGroup(void);
};


#endif /** __VIEW_GROUP_H__ */