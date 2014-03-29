#pragma once

#ifndef __RECTANGLE_VIEW_H_
#define __RECTANGLE_VIEW_H_
#include "FigureView.h"
class RectangleView :	public FigureView
{

private:
	int mWidth;
	int mHeight;

public:

	void setHeight(int height) {mHeight=height;}
	void setWidth(int width) {mWidth=width;}

	int getHeight() {return mHeight;}
	int getWidth() {return mWidth;}


	void draw(SDLScreen & screen);

	RectangleView(int x, int y, int width, int height, Uint32 color, int rotation);
	~RectangleView(void);
};

#endif /** __RECTANGLE_VIEW_H_ */