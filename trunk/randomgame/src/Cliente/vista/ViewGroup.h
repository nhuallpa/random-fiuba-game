#pragma once

#ifndef __VIEW_GROUP_H__
#define __VIEW_GROUP_H__
#include <list>
#include "View.h"
class ViewGroup : 	public View
{
private:
	int mWidth;
	int mHeight;

	std::list<View*> views;

public:
	ViewGroup(int x, int y, int width, int height);

	void add(View* aView);

	void clean();
	
	void update();
	
	void draw(SDLScreen & screen);

	void setHeight(int height) {mHeight=height;}
	void setWidth(int width) {mWidth=width;}

	int getHeight() {return mHeight;}
	int getWidth() {return mWidth;}

	~ViewGroup(void);
};


#endif /** __VIEW_GROUP_H__ */