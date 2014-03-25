#pragma once
#ifndef __FIGURE_VIEW_H_
#define __FIGURE_VIEW_H_
#include "View.h"
#include "TextureManager.h"
class FigureView : 	public View
{
private:
	std::string imageId;
public:
	FigureView(std::string imageId, int x, int y, int width, int height);
	~FigureView(void);

	void clean();
	
	void update();

	void draw(SDLScreen & screen);

};
#endif /* defined(__FIGURE_VIEW_H_) */
